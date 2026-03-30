import socket
import struct
import time

SERVER_IP = '127.0.0.1'
SERVER_PORT = 8080

def send_half_packet():
    print("=== 测试场景 2:半包模拟 ===")
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((SERVER_IP, SERVER_PORT))
    
    payload = b"Hello Reactor, this is a half packet test!"
    # !I 表示网络字节序 (大端) 的 4 字节无符号整数
    header = struct.pack('!I', len(payload)) 
    
    # 恶劣环境制造：先发 4 字节包头 + 前 5 个字节的载荷
    s.send(header + payload[:5])
    print("已发送包头和前半截数据，等待 2 秒...")
    
    time.sleep(2) # 此时你的 C++ 服务端必须安静等待，绝不能切包或断开
    
    # 发送剩下的载荷
    s.send(payload[5:])
    print("已发送后半截数据！")
    
    s.close()
    time.sleep(1)

def send_sticky_packet():
    print("\n=== 测试场景 3:粘包模拟 ===")
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((SERVER_IP, SERVER_PORT))
    
    payload1 = b"Packet 1: AAA"
    header1 = struct.pack('!I', len(payload1))
    
    payload2 = b"Packet 2: BBBBBBB"
    header2 = struct.pack('!I', len(payload2))
    
    # 恶劣环境制造：把两个完整的包死死粘在一起，一次性砸过去
    sticky_data = header1 + payload1 + header2 + payload2
    s.sendall(sticky_data)
    print("已一次性发送两个粘连的完整包！")
    
    s.close()

if __name__ == '__main__':
    send_half_packet()
    send_sticky_packet()