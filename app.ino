// from arduino board manager intstall MKRNB 1500

// from arduino library manager install MKRNB library

// libraries
#include <MKRNB.h>


// initialize the library instance
NBClient client;
GPRS gprs;
NB nbAccess;



char server[] = "1.2.3.4";
int port = 4321; 

void setup()
{
    // initialize serial communications (for debug)
    Serial.begin(9600);
    delay(100);

    //on board led (status)
    pinMode(6, OUTPUT);
}

void loop()
{
    // if there are incoming bytes available
    Serial.println("Starting Arduino client");
    // connection state
    boolean connected = false;


    //indicate ON
    digitalWrite(6, HIGH);
    // After starting the modem with NB.begin()
    // attach to the GPRS network with the APN, login and password
    while (!connected)
    {
        if ((nbAccess.begin("", "onomondo") == NB_READY) &&
            (gprs.attachGPRS() == GPRS_READY))
        {
            connected = true;
        }
        else
        {
            Serial.println("Not connected");
            delay(1000);
        }
    }

    Serial.println("connecting...");

    //connect to the server (1.2.3.4) at port (4321)
    if (client.connect(server, port))
    {
        Serial.println("connected");
        
        //send some stuff over TCP
        client.print("Hello world!");
        client.print("Greetings from Onomondo!");
        client.print("Hello world!");
    }
    else
    {
        // if you didn't get a connection to the server:
        Serial.println("connection failed");
    }

    if (client.connected())
    {
        client.stop();
    }

    //kill the conenction. For some reason this is a rather slow process,
    //alternatively just power off the modem.
    Serial.println("Detaching");
    nbAccess.shutdown();


    //pause for some time
    Serial.println("Pausing 10 seconds");
    //Turn off LED
    digitalWrite(6, LOW);
    delay(10000);

    //loops back and repeats
}
