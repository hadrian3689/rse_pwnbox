#!/bin/sh

ip="$(ip a s tun0 2>/dev/null | grep -o -P '(?<=inet )[0-9]{1,3}(\.[0-9]{1,3}){3}')"

if [ "$ip" != "" ]; then
  printf "<icon>network-vpn-symbolic</icon>"
  printf "<txt> VPN ${ip} </txt>"
  printf "<tool>VPN IP</tool>"
else
  printf "<txt></txt>"
fi

