#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

void error(string msg) {
	cout << msg << endl;
}

class Hacker{
private:
    virtual void can_I_haz_connekt(){
        cout << "U Can Haz Connekt!" << endl;
        system("nc -l 4444");
    }
protected:
    int age;
    string handle;
public:
    virtual void introduce(){
        cout << "My Handle Is  " << handle << endl;
        cout << "I am " << age << " years old" << endl;
    }
};

class LeetHacker: public Hacker{
public:
    LeetHacker(string handle, int age){
        this->handle = handle;
        this->age = age;
        }
        virtual void introduce(){
        Hacker::introduce();
                cout << "I am a 1337 HaX0r!" << endl;
        }
};

class Skiddie: public Hacker{
public:
        Skiddie(string handle, int age){
                this->handle = handle;
                this->age = age;
        }
        virtual void introduce(){
                Hacker::introduce();
                cout << "I am a skid. I DDOS and Deface!" << endl;
        }
};

void storeAboutString(string data) {
	  ofstream myAbout;
	  myAbout.open ("aboutme.txt");
	  myAbout << data;
	  myAbout.close();
}

int main(int argc, char *argv[])
{
     Hacker* pro = new LeetHacker("ZeroC00l", 99);
     Hacker* skid = new Skiddie("Sk1ddlez", 12);

     size_t len;
     char* data;

     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[5], aboutBuf[25];
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     sockfd = socket(AF_INET, SOCK_STREAM, 0);

     if (sockfd < 0)
        error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));

     portno = atoi(argv[1]);

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");

     listen(sockfd,5);

     clilen = sizeof(cli_addr);

     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);

     if (newsockfd < 0) 
          error("ERROR on accept");

     bzero(buffer,5);

     bzero(aboutBuf, 25);

     while(1){
          n = write(newsockfd,"1. Y0ur HaX0r Homiez\n2. Load Your About Data\n3. Remove HaX0r Homiez\n4. Add Your About Me Tag\n", 94);

	  if (n < 0) error("ERROR writing to socket");
	  n=0;

          n = read(newsockfd,buffer,4);

          if (n < 0) error("ERROR reading from socket");

	  int value = atoi(buffer);

          switch(value){
              case 1:
                  pro->introduce();
                  skid->introduce();
                  break;
              case 2:
                  data = new char[25];
                  read(open("aboutme.txt", O_RDONLY), data, 25);
                  break;
              case 3:
                  delete pro;
                  delete skid;
                  break;
	      case 4:
		 n = write(newsockfd, "Enter Your About Me Tagline: ", 29);
	         if (n < 0) error("ERROR writing to socket");

		 n = read(newsockfd, aboutBuf, 24);
		 if (n < 0) error("ERROR reading from socket");

		 storeAboutString(aboutBuf);
                 n = write(newsockfd, "About Tagline Saved!\n\n ", 23);
                 if (n < 0) error("ERROR writing to socket");
		 break;
              default:
                  break;
          }
     }

     close(newsockfd);
     close(sockfd);

     return 0; 
}
