# UseMeImFree
A Linux server binary with a remote use after free vulnerability.

After having a great time exploiting a UAF vuln with help from @FuzzySec, @rotlogix and @magicmac2000 on https://www.fuzzysecurity.com I decided to share in that fun and step up the given vuln binary to give it a remote vuln that we can exploit over the wire. So I took the source code given from @fuzzysec's tutorial which first came from pwnable.kr and gave it some server stuff to let us exploit it remotely. I also changed up the theming a little and added a feature that lets you create a text file on the server.


****Still a work in progress but a fun binary to play with****

I will provide a write up shortly on how to hack this. In the meantime for help visit: http://fuzzysecurity.com/tutorials/expDev/13.html


<b>Compile:</b> gcc usemeimfree.cpp -o usemeimfree -lstdc++

<b>Execution:</b> ./usemeimfree <port> - Ex: ./usemeimfree 12120
  
 <b>Once executed, remotely telnet into the machine running UseMeImFree on the port you chose.</b>
