import socket
import struct
import time

HOST = '127.0.0.1'
PORT = 8080

def create_packet(msg):
    # !I 表示大端无符号整型 (4字节)，与 C++ 的 ntohl/htonl 对应
    return struct.pack('!I', len(msg.encode())) + msg.encode()

def test_1_normal():
    print("\n--- 场景 1: 发送完整包 (正常流) ---")
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall(create_packet("Hello, Phase 1.5 Reactor!"))
        time.sleep(0.1) # 留出时间给服务端打印日志

def test_2_half_packet():
    print("\n--- 场景 2: 拆成两次发 (验证半包拦截) ---")
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        msg = "This is a strict half packet test."
        encoded_msg = msg.encode()
        
        # 先发4字节头部
        s.sendall(struct.pack('!I', len(encoded_msg)))
        print("  -> 🔫 已发送 4 Bytes 头部，故意休眠 1 秒制造网络延迟...")
        time.sleep(1)
        
        # 再发 Payload
        s.sendall(encoded_msg)
        print("  -> 🔫 已补发剩余 Payload 数据")
        time.sleep(0.1)

def test_3_sticky_packet():
    print("\n--- 场景 3: 连发两个包 (验证粘包精准切割) ---")
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        packet1 = create_packet("First Packet in Sticky Stream.")
        packet2 = create_packet("Second Packet sticking right behind.")
        
        # 拼在一起，一次性通过 TCP 缓冲区推过去
        print("  -> 🔫 将两个包揉进同一个 sendall 中发送...")
        s.sendall(packet1 + packet2)
        time.sleep(0.1)

def test_4_oom_meltdown():
    print("\n--- 场景 4: 10MB 超大非法前缀 (验证 OOM 熔断与强杀) ---")
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        
        # 伪造一个 10MB 的长度前缀 (超过你代码里 4MB 的 MAX_PAYLOAD_SIZE)
        fake_length = 10 * 1024 * 1024
        s.sendall(struct.pack('!I', fake_length))
        print(f"  -> 🔫 已发送伪造长度: {fake_length} Bytes，等待服务端触发物理拔线...")
        time.sleep(0.2)
        
        # 此时服务端应该已经抛出错误并 close(curr_fd) 了，我们尝试继续发数据会引发 Broken Pipe 异常
        try:
            s.sendall(b"try to send more after meltdown")
        except Exception as e:
            print(f"  -> ✅ 预期内的连接异常 (证明服务端已硬切断): {e}")

def test_5_connect_and_drop():
    print("\n--- 场景 5: 建立连接后直接强退 (验证 recv == 0 清理) ---")
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    print("  -> 🔫 已建立连接，马上执行 socket.close() 模拟客户端意外死亡")
    s.close()
    time.sleep(0.1)

if __name__ == "__main__":
    print("🚀 末日测试自动化脚本启动！")
    time.sleep(1)
    
    test_1_normal()
    time.sleep(0.5)
    
    test_2_half_packet()
    time.sleep(0.5)
    
    test_3_sticky_packet()
    time.sleep(0.5)
    
    test_4_oom_meltdown()
    time.sleep(0.5)
    
    test_5_connect_and_drop()
    
    print("\n🏁 所有 5 大极限场景轰炸完毕！")