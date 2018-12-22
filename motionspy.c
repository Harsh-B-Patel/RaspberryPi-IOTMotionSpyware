#include <stdio.h>
#include <wiringPi.h>
#include <curl/curl.h>
#include <time.h>
/*
This is made by harsh patel and gives full right to reuse and duplicate the code withput any credition to ownwer.
this code only works if u have CURL Library downloaded on your Raspberry pi

CURL Library can be downloaded by running these 3 commands one by one in the terminal.
It may take 10 mins to download and install the updates.

  sudo apt-get update
  sudo apt-get upgrade
  sudo apt-get install libcurl4-openssl-dev

*/
#define BUFFER_MAX 4096

/*
will send an ifttt request with 3 inputs.
*/
int ifttt(char*where, char *v1, char *v2, char *v3)
{
  CURL *curl;
  CURLcode res;
  struct curl_slist *headers = NULL;
  char sbuf[BUFFER_MAX];

  sprintf(sbuf, "{ \"value1\" : \"%s\", \"value2\" : \"%s\", \"value3\" : \"%s\"}", v1, v2, v3);

  /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, where);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, sbuf);
    headers = curl_slist_append(headers,"Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fopen("/dev/null", "w"));

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return(res == CURLE_OK);
  }
  curl_global_cleanup();
  return 0;
}

int main(int argc, char *argv[])
{
  wiringPiSetup() ;
  pinMode(0, INPUT); // motion sensor input ( plug in position of pin 0 i.e. phys11 refer to the image in github shows where all the pins are )
  while(1) {
    if(digitalRead(0) == 1){ //if motion sensosed then execute the ifttt method for webhook
      //ifttt(ENTER YOUR OWN WEBHOOK IN THE FORM OF " https://maker.ifttt.com/trigger/{event}/with/key/{key}", "VALUE3", "VALUE2", "VALUE!");
      delay(5000);// to check if someone moves again set delay as per personal descretion
  }

  }
  return 0 ;
}
