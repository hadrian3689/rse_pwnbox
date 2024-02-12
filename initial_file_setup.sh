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

pentest_tools () {
        mkdir /opt/chisel && mkdir /opt/pspy && mkdir /opt/peas && mkdir /opt/statics
        wget "https://github.com/andrew-d/static-binaries/raw/master/binaries/linux/x86_64/nmap" -O /opt/statics/nmap
        wget "https://github.com/int0x33/nc.exe/raw/master/nc64.exe" -O /opt/statics/nc64.exe

        api_url="https://api.github.com/repos/carlospolop/PEASS-ng/releases/latest"
        download_url=$(curl -s "$api_url" | jq -r ".assets[0].browser_download_url")
        name="linpeas.sh"
        curl -L -o $name "$download_url"
        echo "Downloaded $name"
        mv $name /opt/peas/$name

        download_url=$(curl -s "$api_url" | jq -r ".assets[11].browser_download_url")
        name="winPEASx64.exe"
        curl -L -o $name "$download_url"
        echo "Downloaded $name"
        mv $name /opt/peas/$name

        api_url="https://api.github.com/repos/jpillora/chisel/releases/latest"
        download_url=$(curl -s "$api_url" | jq -r ".assets[4].browser_download_url")
        name="chisel_1.9.1_linux_amd64.gz"
        curl -L -o $name "$download_url"
        echo "Downloaded $name"
        gunzip -c $name > /opt/chisel/chisel && rm $name

        download_url=$(curl -s "$api_url" | jq -r ".assets[21].browser_download_url")
        name="chisel_1.9.1_windows_amd64.gz"
        curl -L -o $name "$download_url"
        echo "Downloaded $name"
        gunzip -c $name > /opt/chisel/chisel.exe && rm $name

        api_url="https://api.github.com/repos/DominicBreuker/pspy/releases/latest"
        name="pspy64"
        download_url=$(curl -s "$api_url" | jq -r ".assets[2].browser_download_url")
        curl -L -o $name "$download_url"
        echo "Downloaded $name"
        mv $name /opt/pspy/$name

        api_url="https://api.github.com/repos/NationalSecurityAgency/ghidra/releases/latest"
        download_url=$(curl -s "$api_url" | jq -r ".assets[0].browser_download_url")
        name="ghidra.zip"
        curl -L -o $name "$download_url"
        echo "Downloaded $name"
        unzip $name -d /opt/ && rm $name
        new_zsh_terminal
}

file_moving () {
        echo "Copying background images"
        mkdir /usr/share/backgrounds/rse
        cp -R backgrounds/* /usr/share/backgrounds/rse/

        echo "Copying VPN Panel IP display script"
        cp /usr/share/kali-themes/xfce4-panel-genmon-vpnip.sh /usr/share/kali-themes/xfce4-panel-genmon-vpnip.sh.bak
        cp xfce4-panel-genmon-vpnip.sh /usr/share/kali-themes/xfce4-panel-genmon-vpnip.sh
        chmod +x /usr/share/kali-themes/xfce4-panel-genmon-vpnip.sh

        echo "Generating Reverse Shell Program"
        gcc revshell_gen.c -o revshell
        mv revshell /usr/bin/revshell
        chmod +x /usr/bin/revshell

        echo "Copying icon files"
        cp -R rse/ /usr/share/icons/
        cp -R Material-Black-Lime-Numix-FLAT/ /usr/share/icons/
        pentest_tools
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