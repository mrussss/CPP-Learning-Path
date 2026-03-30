import socket
import struct
import time

def send_packet(ip, port, length_val):
    # 1. 苦力活：建立 TCP 连接
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        client.connect((ip, port))
        
        # 👉 2. 【你的核心任务】：查阅 Python struct 库，使用 pack 把 length_val 压制成 4 字节网络大端序！
        # 提示：格式符是 '!I'
        # header = struct.pack(你的代码)
        header = struct.pack('!I',length_val)
        
        # 3. 苦力活：发包
        client.sendall(header)
        print(f"[*] 客户端已发送指示长度: {length_val}")
        
        # 稍微等一下，让 C++ 服务端的 epoll 反应过来
        time.sleep(0.5)
        
    except Exception as e:
        print(f"[!] 发送失败: {e}")
    finally:
        client.close()

if __name__ == '__main__':
    # 【实弹演练：场景 1（正向解析验证）】
    print("--- 场景 1:发送合法包头 (1024) ---")
    send_packet('127.0.0.1', 8080, 1024)
    
    time.sleep(1)
    
    # 【实弹演练：场景 4（反向 OOM 熔断验证）】
    # 你的 C++ 设定的 MAX_PAYLOAD_SIZE 是 4 * 1024 * 1024 (4MB)
    print("\n--- 场景 4:发送非法超大包头 (5MB,触发熔断) ---")
    send_packet('127.0.0.1', 8080, 5 * 1024 * 1024)