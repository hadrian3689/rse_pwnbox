#!/bin/sh

tun="$(ip a s tun0 2>/dev/null | grep -o -P '(?<=inet )[0-9]{1,3}(\.[0-9]{1,3}){3}')"
eth="$(ip a s eth0 2>/dev/null | grep -o -P '(?<=inet )[0-9]{1,3}(\.[0-9]{1,3}){3}')"
eth1="$(ip a s eth1 2>/dev/null | grep -o -P '(?<=inet )[0-9]{1,3}(\.[0-9]{1,3}){3}')"
lo="$(ip a s lo 2>/dev/null | grep -o -P '(?<=inet )[0-9]{1,3}(\.[0-9]{1,3}){3}')"

if [ "$tun" != "" ]; then
  printf "<icon>network-vpn-symbolic</icon>"
  printf "<txt> VPN ${tun} </txt>"
  printf "<tool>VPN IP</tool>"
elif [ "$tun" != "" ] && [ "$eth1" != "" ]; then
  printf "<icon>network-vpn-symbolic</icon>"
  printf "<txt> VPN ${tun} | ${eth1} </txt>"
  printf "<tool>VPN IP</tool>"
elif [ "$eth" != "" ] && [ "$eth1" != "" ]; then
  printf "<icon>network-vpn-symbolic</icon>"
  printf "<txt> IP ${eth} | ${eth1} </txt>"
  printf "<tool>My IP</tool>"
elif [ "$eth" != "" ]; then
  printf "<icon>network-vpn-symbolic</icon>"
  printf "<txt> IP ${eth} </txt>"
  printf "<tool>My IP</tool>"
else
  printf "<icon>network-vpn-symbolic</icon>"
  printf "<txt> IP ${lo} </txt>"
  printf "<tool>My IP</tool>"
fi
