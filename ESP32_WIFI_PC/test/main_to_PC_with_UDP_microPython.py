# pyright: reportMissingImports=false
# 整体流程 这是microPython的代码，主要是实现通过UDP协议接收数据并进行处理的功能。具体流程如下：
# 1. 链接 Wi-Fi
# 2. 启动网络功能（UDP）
# 3. 接收网络数据
# 4. 处理接收的数据

import socket
import time
import network


def do_connect():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        print("connecting to network...")
        wlan.connect("dongfeiqiu", "wangmingdong1225")  # 输入 Wi-Fi 热点账号和密码
        i = 1
        while not wlan.isconnected():
            print("正在链接...{}".format(i))
            i += 1
            time.sleep(1)
    print("network config:", wlan.ifconfig())


def start_udp():
    # 2. 启动网络功能（UDP）

    # 2.1. 创建 UDP 套接字
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # 2.2. 绑定本地信息
    udp_socket.bind(("0.0.0.0", 7788))

    return udp_socket


def main():
    # 1. 链接 Wi-Fi
    do_connect()
    # 2. 创建 UDP
    udp_socket = start_udp()
    # 3. 接收网络数据
    while True:
        recv_data, sender_info = udp_socket.recvfrom(1024)
        print("{}发送{}".format(sender_info, recv_data))

        try:
            recv_data_str = recv_data.decode("utf-8")
            print(recv_data_str)
        except Exception as ret:
            print("error:", ret)
            continue

        # 4. 处理接收的数据
        if recv_data_str == "light on":
            print("这里是要灯亮的代码...")
            # led.value(1)
        elif recv_data_str == "light off":
            print("这里是要灯灭的代码...")
            # led.value(0)
        else:
            # 返回错误提示
            msg = "please input light on or light off"
            # 发送给对方的 IP 地址和端口
            dest_ip = sender_info[0]
            dest_port = int(sender_info[1])
            udp_socket.sendto(msg.encode("utf-8"), (dest_ip, dest_port))


if __name__ == "__main__":
    main()