#!/bin/bash

new_pwsh_terminal () {
	echo "Changing powershell terminals"
	for homedir in /home/*; do cp -R "$homedir"/.config/powershell/Microsoft.PowerShell_profile.ps1 "$homedir"/.config/powershell/Microsoft.PowerShell_profile.ps1.bak; done
	for homedir in /home/*; do cp Microsoft.PowerShell_profile.ps1 "$homedir"/.config/powershell/Microsoft.PowerShell_profile.ps1; done
	mkdir ~/.config
	mkdir ~/.config/powershell
	cp Microsoft.PowerShell_profile.ps1 ~/.config/powershell/
	echo "Done! Open up new Powershell terminal to see the changes"
	echo "Your original terminals are in ~/.config/powershell/Microsoft.PowerShell_profile.ps1.bak for each user"
	exit 0
}

new_zsh_terminal () {
	echo "Changing zshrc terminals"
	for homedir in /home/*; do cp "$homedir"/.zshrc "$homedir"/.zshrc.bak; done 
	for homedir in /home/*; do cp zshrc "$homedir"/.zshrc; done
	cp ~/.zshrc ~/.zshrc.bak 
	cp zshrc ~/.zshrc
	echo "Done! Open up a terminal to see the changes!"
	echo "Your original terminals are in ~./zshrc.bak for each user"
	new_pwsh_terminal
}

file_moving () {
	echo "Copying background images"
	mkdir /usr/share/backgrounds/rse
	cp -R backgrounds/* /usr/share/backgrounds/rse/
	
	echo "Copying VPN Panel IP display script"
	cp /usr/share/kali-themes/xfce4-panel-genmon-vpnip.sh /usr/share/kali-themes/xfce4-panel-genmon-vpnip.sh.bak
	cp xfce4-panel-genmon-vpnip.sh /usr/share/kali-themes/xfce4-panel-genmon-vpnip.sh
	chmod +x /usr/share/kali-themes/xfce4-panel-genmon-vpnip.sh

	echo "Copying icon files"
	cp -R rse/ /usr/share/icons/
	cp -R Material-Black-Lime-Numix-FLAT/ /usr/share/icons/
	new_zsh_terminal

}

root_check () {
	if [[ "$(whoami)" != root ]]; then
		echo "You are not root. You are the $(whoami) user. Run this script as root with sudo ./initial_file_setup.sh or or sudo su to root and ./initial_file_setup.sh :)"
		exit 1
	else
		echo "You are root :) let's begin"
		file_moving
	fi
}

root_check
