## Routing. Example.

<img src="../misc/images/network_route.png" alt="network_route" width="500"/>

Let's take a look at an example of an infrastructure with multiple subnets.

As you can see in the example below, the first entry (line) is for network *128.17.75.0/24*, all packets for this network will be sent to gateway *128.17.75.20*, which is the IP address of the host itself.
The second entry is the default route that will be used for all packets sent on the network that are not specified in this routing table. Here, the route is through the papaya host (IP *128.17.75.98*), which is like a door to the outside world. This route must be written to all machines on the *128.17.75.0/24* network that need access to other networks. The third entry is for the loopback interface. This address is used when the machine needs to connect to itself via **TCP/IP**.

The last entry in the routing table is for IP *128.17.75.20* and is routed to the lo interface, so if the machine connects to itself on *128.17.75.20*, all packets will be sent to the *127.0.0.1* interface.

An example of a routing table for an eggplant host:
```
[root@eggplant ~]# netstat -rn
Kernel IP routing table
Destination     Gateway         Genmask         Flags   MSS Window  irtt Iface
128.17.75.0      128.17.75.20   255.255.255.0   UN        1500 0          0 eth0
default          128.17.75.98   0.0.0.0         UGN       1500 0          0 eth0
127.0.0.1        127.0.0.1      255.0.0.0       UH        3584 0          0 lo
128.17.75.20     127.0.0.1      255.255.255.0   UH        3584 0          0 lo
```

When the eggplant host wants to send a packet to the zucchini host (so the packet will contain a source — *128.17.75.20* and a destination — *128.17.75.37*), the IP protocol will determine from the routing table that both hosts belong to the same network and will send the packet directly to the network where zucchini will receive it.
More specifically, the network interface controller sends an **ARP** request — "Who is IP *128.17.75.37*? This is *128.17.75.20* yelling".

All machines receiving this message ignore it, and the host at *128.17.75.37* replies "That's me, and my MAC address is such-and-such...", then they connect and exchange data based on **ARP** tables where IP-MAC addresses are matched. "Yelling" packet is sent to all hosts. This happens because the recipient's MAC address is specified as a broadcast address (*FF:FF:FF:FF:FF:FF:FF*).
Such packets are received by all hosts on the network.

Let's consider a situation where a host eggplant wants to send a packet to a host pear, for example, or even further away?
In this case, the destination of the packet will be *128.17.112.21*, the IP protocol will try to find a route for *128.17.112* in the routing table, but this route is not there, so it will choose the default route, whose gateway is papaya (*128.17.75.98*).

After receiving the packet, papaya will look up the destination address in its routing table:
```
[root@papaya ~]# netstat -rn
Kernel IP routing table
Destination     Gateway         Genmask         Flags   MSS Window  irtt Iface
128.17.75.0      128.17.75.98   255.255.255.0   UN        1500 0          0 eth0
128.17.112.0     128.17.112.3   255.255.255.0   UN        1500 0          0 eth1
default          128.17.112.40  0.0.0.0         UGN       1500 0          0 eth1
127.0.0.1        127.0.0.1      255.0.0.0       UH        3584 0          0 lo
128.17.75.98     127.0.0.1      255.255.255.0   UH        3584 0          0 lo
128.17.112.3     127.0.0.1      255.255.255.0   UH        3584 0          0 lo
```

In this example you can see that papaya is connected to two networks: *128.17.75.0/24* via the eth0 device and *128.17.112* via the eth1 device.

The default route is through the pineapple host, which is the gateway to the external network.

Therefore, after receiving the pear packet, the papaya router will see that the destination address belongs to *128.17.112*, and will route the packet according to the second entry in the routing table.

This is how packets are passed from router to router until they reach their destination address.

## **ICMP** protocol

The **ICMP** protocol is an error notification protocol.

The TCP/IP stack has a special messaging mechanism to allow routers to notify network nodes of errors or abnormal situations, called the Internet Control Message Protocol (**ICMP**).
