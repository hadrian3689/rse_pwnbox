#!/bin/sh

tun="$(ip a s tun0 2>/dev/null | grep -o -P '(?<=inet )[0-9]{1,3}(\.[0-9]{1,3}){3}')"
eth="$(ip a s eth0 2>/dev/null | grep -o -P '(?<=inet )[0-9]{1,3}(\.[0-9]{1,3}){3}')"

if [ "$tun" != "" ]; then
  printf "<icon>network-vpn-symbolic</icon>"
  printf "<txt> VPN ${tun} </txt>"
  printf "<tool>VPN IP</tool>"
else
  printf "<icon>network-vpn-symbolic</icon>"
  printf "<txt> IP ${eth} </txt>"
  printf "<tool>VPN IP</tool>"
fi