#include "wordclock.h"
#include "rtc.h"
#include "patterns.h"
#include "matrix.h"
//#include "DS1307.h"

uint8_t time[8] = {0};
int count = 0;

//void obtainTime()
//{
//    /* Getting current time and converting it to a usable
//       format
//    */
////    time_t rawtime;
////    time(&rawtime);
////    char buff[100] = {0};
////    strftime(buff, sizeof buff, "%F %T", localtime(&rawtime));
//
//    /* RTC Initialization */
//    rtcInit(&hi2c1);
//    char timeBuffer[DS1307_MINIMAL_BUFFER_LENGTH];
////    setDateTime(buff, DS1307_MINIMAL_BUFFER_LENGTH);
//    setDateTime("2021-05-28 16:07:55", DS1307_MINIMAL_BUFFER_LENGTH);
//    getDateTime(&timeBuffer[0], DS1307_MINIMAL_BUFFER_LENGTH);
//}

void displayTime()
{   
  RTC_DateTypeDef gDate;
  RTC_TimeTypeDef gTime;
  /* Get the RTC current Time */
  HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);

  if ((gTime.Minutes > 4) && (gTime.Minutes < 10))
  {
    combineTime(0); //MFIVE
    //Serial.print("five");
  }
  if ((gTime.Minutes > 9) && (gTime.Minutes < 15))
  {
    combineTime(1); //MTEN
    //Serial.print("ten");
  }
  if ((gTime.Minutes > 14) && (gTime.Minutes < 20))
  {
    combineTime(2); //AQUARTER
    //Serial.print("a quarter");
  }
  if ((gTime.Minutes > 19) && (gTime.Minutes < 25))
  {
    combineTime(3); //TWENTY;
    //Serial.print("twenty");
  }
  if ((gTime.Minutes > 24) && (gTime.Minutes < 30))
  {
    //TWENTY MFIVE
    combineTime(3);
    combineTime(0);
    //Serial.print("twenty five");
  }
  if ((gTime.Minutes > 29) && (gTime.Minutes < 35))
  {
    combineTime(4); //HALF;
    //Serial.print("half");
  }
  if ((gTime.Minutes > 34) && (gTime.Minutes < 40))
  {
    //TWENTY MFIVE
    combineTime(3);
    combineTime(0);
    //Serial.print("twenty five");
  }
  if ((gTime.Minutes > 39) && (gTime.Minutes < 45))
  {
    combineTime(3); //TWENTY;
    //Serial.print("twenty");
  }
  if ((gTime.Minutes > 44) && (gTime.Minutes < 50))
  {
    combineTime(2); //AQUARTER
    //Serial.print("a quarter");
  }
  if ((gTime.Minutes > 49) && (gTime.Minutes < 55))
  {
    combineTime(16); //TEN
    //Serial.print("ten");
  }
  if (gTime.Minutes > 54)
  {
    combineTime(0); //MFIVE
    //Serial.print("five");
  }

  if ((gTime.Minutes < 5))
  {
    switch (gTime.Hours)
    {
    case 1:
    case 13:
      combineTime(7); //ONE
      break;
    case 2:
    case 14:
      combineTime(8); //TWO
      break;
    case 3:
    case 15:
      combineTime(9); //THREE
      break;
    case 4:
    case 16:
      combineTime(10); //FOUR
      break;
    case 5:
    case 17:
      combineTime(11); //FIVE
      break;
    case 6:
    case 18:
      combineTime(12); //SIX
      break;
    case 7:
    case 19:
      combineTime(13); //SEVEN
      break;
    case 8:
    case 20:
      combineTime(14); //EIGHT
      break;
    case 9:
    case 21:
      combineTime(15); //NINE
      break;
    case 10:
    case 22:
      combineTime(16); //TEN
      break;
    case 11:
    case 23:
      combineTime(17); //ELEVEN
      break;
    case 0:
    case 12:
      combineTime(18); //TWELVE
      break;
    }
  }
  else if ((gTime.Minutes < 35) && (gTime.Minutes > 4))
  {
    combineTime(5); //PAST
    //Serial.print(" past ");
    switch (gTime.Hours)
    {
    case 1:
    case 13:
      combineTime(7); //ONE
      break;
    case 2:
    case 14:
      combineTime(8); //TWO
      break;
    case 3:
    case 15:
      combineTime(9); //THREE
      break;
    case 4:
    case 16:
      combineTime(10); //FOUR
      break;
    case 5:
    case 17:
      combineTime(11); //FIVE
      break;
    case 6:
    case 18:
      combineTime(12); //SIX
      break;
    case 7:
    case 19:
      combineTime(13); //SEVEN
      break;
    case 8:
    case 20:
      combineTime(14); //EIGHT
      break;
    case 9:
    case 21:
      combineTime(15); //NINE
      break;
    case 10:
    case 22:
      combineTime(16); //TEN
      break;
    case 11:
    case 23:
      combineTime(17); //ELEVEN
      break;
    case 0:
    case 12:
      combineTime(18); //TWELVE
      break;
    }
  }
  else
  {
    // if we are greater than 34 Minutes past the Hours then display
    // the next Hours, as we will be displaying a 'to' sign
    combineTime(6); //TO;
    //Serial.print(" to ");
    switch (gTime.Hours)
    {
    case 1:
    case 13:
      combineTime(8); //TWO
      break;
    case 14:
    case 2:
      combineTime(9); //THREE
      break;
    case 15:
    case 3:
      combineTime(10); //FOUR
      break;
    case 4:
    case 16:
      combineTime(11); //FIVE
      break;
    case 5:
    case 17:
      combineTime(12); //SIX
      break;
    case 6:
    case 18:
      combineTime(13); //SEVEN
      break;
    case 7:
    case 19:
      combineTime(14); //EIGHT
      break;
    case 8:
    case 20:
      combineTime(15); //NINE
      break;
    case 9:
    case 21:
      combineTime(16); //TEN
      break;
    case 10:
    case 22:
      combineTime(17); //ELEVEN
      break;
    case 11:
    case 23:
      combineTime(18); //TWELVE
      break;
    case 0:
    case 12:
      combineTime(7); //ONE
      break;
    }
  }
  
  HAL_Delay(2);
  
  maxInit(); // Initialize the Dot Matrix
  
  for(int i=0; i<8; i++)
  {
      writeMax((i+1), time[i]);
  }
}

void combineTime(int row)
{     
    for (int i = 0; i < 8; i++)
    {
        time[i] |= Pattern[row][i];
    }
    count++;
}

void clockTest()
{
    maxInit(); // Initialize the Dot Matrix
    for(int j=0; j<19; ++j)
    {
        for (int i = 0; i < 8; i++)
        {
            writeMax((i+1),Pattern[j][i]);
        }
        HAL_Delay(1000);
    }
}

void timeReset()
{
    for (int t = 0; t < 8; ++t)
    {
        time[t] = 0;
    }
}
