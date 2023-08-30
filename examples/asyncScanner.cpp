#include <Arduino.h>
#include <RX5808.h>

RX5808 RX1(21, 22, 19, 37);
RX5808 RX2(21, 23, 19, 38);
RX5808 RX3(21, 25, 19, 39);
RX5808 RX4(21, 26, 19, 36);

TaskHandle_t vTaskRX1;
TaskHandle_t vTaskRX2;
TaskHandle_t vTaskRX3;
TaskHandle_t vTaskRX4;

uint16_t raw_rssi[8];
uint8_t channels = 8;
bool powerState = 1;
uint16_t loopcount = 0;
unsigned long startmillis = 0;

SemaphoreHandle_t rssiSemaphore;
void createSemaphore(){
    rssiSemaphore = xSemaphoreCreateMutex();
    xSemaphoreGive( ( rssiSemaphore) );
}

void asyncRSSI(RX5808 &RX, uint16_t module_channel) {
    const TickType_t xDelay = RX.getMinTuneTime() / portTICK_PERIOD_MS;

    RX.setChannel(module_channel, 0);
    vTaskDelay( xDelay );
    xSemaphoreTake(rssiSemaphore, portMAX_DELAY);
    raw_rssi[module_channel] = RX.getRSSI();
    xSemaphoreGive(rssiSemaphore);
}

void genericTaskCode(RX5808 RX, TaskHandle_t handle, uint8_t module_channels[], uint8_t size) {
    RX.powerUp();
    RX.disableTuneTime();
    for( ;; )
    {
        for (size_t i = 0; i < size; i++)
        {
            asyncRSSI(RX, module_channels[i]);
        }
        vTaskSuspend( handle );
    }
}

void vTaskRX1Code( void * pvParameters ) {
    uint8_t module_channels[] = {0, 1};
    genericTaskCode(RX1, vTaskRX1, module_channels, sizeof(module_channels));
}

void vTaskRX2Code( void * pvParameters ) {
    uint8_t module_channels[] = {2, 3};
    genericTaskCode(RX2, vTaskRX2, module_channels, sizeof(module_channels));
}

void vTaskRX3Code( void * pvParameters ) {
    uint8_t module_channels[] = {4, 5};
    genericTaskCode(RX3, vTaskRX3, module_channels, sizeof(module_channels));
}

void vTaskRX4Code( void * pvParameters ) {
    uint8_t module_channels[] = {6, 7};
    genericTaskCode(RX4, vTaskRX4, module_channels, sizeof(module_channels));
}

void setup() {
    Serial.begin(115200);
    delay(2000);

    createSemaphore();

    xTaskCreate( vTaskRX1Code, "vTaskRX1", 10000, NULL, 0, &vTaskRX1 );
    xTaskCreate( vTaskRX2Code, "vTaskRX2", 10000, NULL, 0, &vTaskRX2 );
    xTaskCreate( vTaskRX3Code, "vTaskRX3", 10000, NULL, 0, &vTaskRX3 );
    xTaskCreate( vTaskRX4Code, "vTaskRX4", 10000, NULL, 0, &vTaskRX4 );

    Serial.println("Setup Done");
    startmillis = millis();
}

void loop() {
    if(
        eTaskGetState(vTaskRX1) == eSuspended && 
        eTaskGetState(vTaskRX2) == eSuspended && 
        eTaskGetState(vTaskRX3) == eSuspended && 
        eTaskGetState(vTaskRX4) == eSuspended
    ) {
        for (size_t i = 0; i < channels; i++)
        {
            Serial.printf("| %d: %04d ", (int)i+1, (int)raw_rssi[i]);
        }
        Serial.printf("| scanned %d channels in %d millis \n", channels, millis() - startmillis);
        startmillis = millis();
        vTaskResume( vTaskRX1 );
        vTaskResume( vTaskRX2 );
        vTaskResume( vTaskRX3 );
        vTaskResume( vTaskRX4 );
    }
}