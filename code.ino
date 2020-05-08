#include "BH1750.h"

BH1750 sensor(0x23, Wire);

double lightLevel = 0;
int changeFlag = 0;

void setup()
{    
    sensor.begin(); //libray function call to initialise sensor
    sensor.set_sensor_mode(BH1750::forced_mode_high_res2); //set mode based on pre defined constants in library
}

void loop()
{
    
    sensor.make_forced_measurement();
    
    lightLevel = sensor.get_light_level();
    
    /*
    The following code emulates 'state', when the change flag is 0 or 2 and the light level peaks past 50 the
    flag is set to 1 to indicate that sunlight has hit the terrarium and the publish is fired. If it is still sunny on 
    the next iteration the code wont fire as the previous state was also sunny. The same rules apply for when it is dark.
    */
    
        
    if(lightLevel > 50 && changeFlag != 1)
    {
        changeFlag = 1;
        Particle.publish("Sunlight is here!", "It's nice and sunny.", 60, PRIVATE);
    }
    
     if(lightLevel < 50 && changeFlag != 2)
    {
        changeFlag = 2;
        Particle.publish("Oh no darkness!", "Scary times.", 60, PRIVATE);
    }
    
    delay(2000);
}
