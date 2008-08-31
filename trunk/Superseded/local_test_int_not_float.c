#pragma config(Sensor, S1,     leftSonar,           sensorSONAR)
#pragma config(Sensor, S2,     centreSonar,         sensorSONAR)
#pragma config(Sensor, S3,     rightSonar,          sensorSONAR)
#pragma config(Motor,  motorB,          leftMotor,            tmotorNxtEncoderClosedLoop)
#pragma config(Motor,  motorC,          rightMotor,           tmotorNxtEncoderClosedLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

///////////////////////////////////////////////////////////////////////////////////////////////
//
//      Title:- Local cell testing
//      Author:- Lachlan Smith (RobotC)
//               Mark Wakabayashi (Jave version)
//               Michael Milford (original algorithim/c code)
//      Purpose:- Just for testing how well local view works
//
//
///////////////////////////////////////////////////////////////////////////////////////////////

//----include files----//
#include "localNeural.h";
typedef struct
{
  int localView[numNeuralUnits];
} localHolder;


//----General In-Module Variables----//
int numActive = 0; //number of active cells
int currentTheta = 0; //theta for pose and turns
char currentDirection = 0; //direction for pose and turns
int localTemp[numNeuralUnits]; //holds the temporary neural value
int localComparison[numNeuralUnits]; //what the local cell data is loaded into
char nextEmptyCell = 0; //used for holding the next empty cell in the localcell Struct
localHolder poseAssoc[100];
int tempCalc = 0;

//                            //
//----Local View Functions----//
//                            //

//----Initialises the arrays to zero----//
void clearTemp()
{
  memset(localTemp, 0, 2*numNeuralUnits); //sets entire array to zero
  memset(localComparison, 0, 2*numNeuralUnits); //sets entire array to zero
}

void datalogging2(char cellNum)
{
	float time = (float) nPgmTime / 1000;
	int time2 = (int) time;
	AddToDatalog(1, time2);
  AddToDatalog(2,cellNum);
  /*if(nSyncedMotors == synchBC)
  {
    AddToDatalog(3,nMotorEncoder[motorB]);
  }
  else if(nSyncedMotors == synchCB)
  {
  	AddToDatalog(3,nMotorEncoder[motorC]);
  }*/
}


void clearLocal()
{
	memset(poseAssoc, 0, 36*100);
}

//----Set the right neural units----//
void setRight(int rightSonarValue)
{
	//This function allocates a proportion to each neural unit based on the value returned by the sonar sensor
	//rightSonarValue = SensorValue(rightSonar);
	tempCalc = 0;
	if(rightSonarValue <= firstUnit)
	{
		tempCalc = (int) ((100*(firstUnit - rightSonarValue)/firstUnit));
    localTemp[12] = (int) 100 - tempCalc;
	}
  else if(rightSonarValue > firstUnit && rightSonarValue <= secondUnit)
  {
  	tempCalc = (int) (100*(secondUnit - rightSonarValue)/(secondUnit - firstUnit));
    localTemp[12] = tempCalc;
  	localTemp[13] = 100 - tempCalc;
  }
  else if(rightSonarValue > secondUnit && rightSonarValue <= thirdUnit)
  {
  	tempCalc = (int) (100*(thirdUnit - rightSonarValue)/(thirdUnit - secondUnit));
    localTemp[13] = tempCalc;
  	localTemp[14] = 100 - tempCalc;
  }
  else if(rightSonarValue > thirdUnit && rightSonarValue <= fourthUnit)
  {
  	tempCalc = (int) (100*(fourthUnit - rightSonarValue)/(fourthUnit - thirdUnit));
    localTemp[14] = tempCalc;
  	localTemp[15] = 100 - tempCalc;
  }
  else if(rightSonarValue > fourthUnit && rightSonarValue <= fifthUnit)
  {
  	tempCalc = (int) (100*(fifthUnit - rightSonarValue)/(fifthUnit - fourthUnit));
    localTemp[15] = tempCalc;
  	localTemp[16] = 100 - tempCalc;
  }
  else if(rightSonarValue > fifthUnit && rightSonarValue <= sixthUnit)
  {
  	tempCalc = (int) (100*(sixthUnit - rightSonarValue)/(sixthUnit - fifthUnit));
    localTemp[16] = tempCalc;
  	localTemp[17] = 100 - tempCalc;
  }
  else if(rightSonarValue > sixthUnit) //if greater than 195cm
  {
    localTemp[17] = 100;
  }
}

//----Set centre neural units----//
void setCentre(int centreSonarValue)
{
	//This function allocates a proportion to each neural unit based on the value returned by the sonar sensor
	//centreSonarValue = SensorValue(centreSonar);
	tempCalc = 0;
	if(centreSonarValue <= firstUnit)
	{
		tempCalc = (int) ((100*(firstUnit - centreSonarValue)/firstUnit));
    localTemp[6] = (int) 100 - tempCalc;
	}
  else if(centreSonarValue > firstUnit && centreSonarValue <= secondUnit)
  {
  	tempCalc = (int) (100*(secondUnit - centreSonarValue)/(secondUnit - firstUnit));
    localTemp[6] = tempCalc;
  	localTemp[7] = 100 - tempCalc;
  }
  else if(centreSonarValue > secondUnit && centreSonarValue <= thirdUnit)
  {
  	tempCalc = (int) (100*(thirdUnit - centreSonarValue)/(thirdUnit - secondUnit));
    localTemp[7] = tempCalc;
  	localTemp[8] = 100 - tempCalc;
  }
  else if(centreSonarValue > thirdUnit && centreSonarValue <= fourthUnit)
  {
  	tempCalc = (int) (100*(fourthUnit - centreSonarValue)/(fourthUnit - thirdUnit));
    localTemp[8] = tempCalc;
  	localTemp[9] = 100 - tempCalc;
  }
  else if(centreSonarValue > fourthUnit && centreSonarValue <= fifthUnit)
  {
  	tempCalc = (int) (100*(fifthUnit - centreSonarValue)/(fifthUnit - fourthUnit));
    localTemp[9] = tempCalc;
  	localTemp[10] = 100 - tempCalc;
  }
  else if(centreSonarValue > fifthUnit && centreSonarValue <= sixthUnit)
  {
  	tempCalc = (int) (100*(sixthUnit - centreSonarValue)/(sixthUnit - fifthUnit));
    localTemp[10] = tempCalc;
  	localTemp[11] = 100 - tempCalc;
  }
  else if(centreSonarValue > sixthUnit)
  {
    localTemp[11] = 100;
  }
}

//----set left neural units----//
void setLeft(int leftSonarValue)
{
	//This function allocates a proportion to each neural unit based on the value returned by the sonar sensor
	//leftSonarValue = SensorValue(leftSonar);
	tempCalc = 0;
	if(leftSonarValue <= firstUnit)
	{
		tempCalc = (int) ((100*(firstUnit - leftSonarValue)/firstUnit));
    localTemp[0] = (int) 100 - tempCalc;
	}
  else if(leftSonarValue > firstUnit && leftSonarValue <= secondUnit)
  {
  	tempCalc = (int) (100*(secondUnit - leftSonarValue)/(secondUnit - firstUnit));
    localTemp[0] = tempCalc;
  	localTemp[1] = 100 - tempCalc;
  }
  else if(leftSonarValue > secondUnit && leftSonarValue <= thirdUnit)
  {
  	tempCalc = (int) (100*(thirdUnit - leftSonarValue)/(thirdUnit - secondUnit));
    localTemp[1] = tempCalc;
  	localTemp[2] = 100 - tempCalc;
  }
  else if(leftSonarValue > thirdUnit && leftSonarValue <= fourthUnit)
  {
  	tempCalc = (int) (100*(fourthUnit - leftSonarValue)/(fourthUnit - thirdUnit));
    localTemp[2] = tempCalc;
  	localTemp[3] = 100 - tempCalc;
  }
  else if(leftSonarValue > fourthUnit && leftSonarValue <= fifthUnit)
  {
  	tempCalc = (int) (100*(fifthUnit - leftSonarValue)/(fifthUnit - fourthUnit));
    localTemp[3] = tempCalc;
  	localTemp[4] = 100 - tempCalc;
  }
  else if(leftSonarValue > fifthUnit && leftSonarValue <= sixthUnit)
  {
  	tempCalc = (int) (100*(sixthUnit - leftSonarValue)/(sixthUnit - fifthUnit));
    localTemp[4] = tempCalc;
  	localTemp[5] = 100 - tempCalc;
  }
  else if(leftSonarValue > sixthUnit)
  {
    localTemp[5] = 100;
  }
}

//---adds the association between local view and pose----//
void addAssociation(char cellNum)
{
  //creates an association between local view and pose - currently using max activated cell as the one needed but may end
	//up using estimated pose as in RAMP code

	memcpy(poseAssoc[cellNum].localView,localTemp,numNeuralUnits*2);

}

//----Dot multiply two vectors----//
float dotMultiply()
{
  char i;
  float dotValue = 0;
  for(i = 0; i < numNeuralUnits; i++)
  {
    if(localTemp[i]>0)
    {
      dotValue = dotValue + localTemp[i] * (localComparison[i];
    }
  }
  dotValue = (float) (dotValue/10000);
  return dotValue; //return the multiply
}

//----normalise the current view for processing----//
void normaliseTemp()
{
//will normalise the temp ||a|| = sqrt(a1^2 + a2^2 + a3^3)
//normalise by a/||a|| ----THIS IS A DODGY NORMALISE----
	float tempTotal = 0;
	char y;
	for(y = 0; y < numNeuralUnits; y++)
	{
		if(localTemp[y]>0) //only if over zero spend clock cycles
		{
		  tempTotal = tempTotal + localTemp[y]*localTemp[y]; //a.a
	  }
	}
	tempTotal =  (sqrt(tempTotal)); //sqrt(a.a)
	for(y = 0; y < numNeuralUnits; y++)
	{
		if(localTemp[y]>0)
		{
	    localTemp[y] = (int) (100*(localTemp[y]/tempTotal));
	  }
	}
}

//----Gets local view and processes ready for comparison----//
void setTemp()
{
	//initalises temp, get sensor readings and sets the local temp to a normalised neural vector
  clearTemp();
  int rightSonarValue = SensorValue(rightSonar); //obvious
  int leftSonarValue = SensorValue(leftSonar);
  int centreSonarValue = SensorValue(centreSonar);
  setLeft(leftSonarValue);
	setCentre(centreSonarValue);
	setRight(rightSonarValue);
	normaliseTemp();
}

void checkLocalCell()
{
	//uses a normalised version of the localTemp.  The comparison local cells are stored as normalised when 1st created
	char z;
	char match = 0;
	float dotTempValue = 0;
	float tempAngle = 0;
	if(nextEmptyCell == 0)
	{
	  //first localCellView
		addAssociation(nextEmptyCell);
    nextEmptyCell++;
    datalogging2(nextEmptyCell);
   // PlaySound(soundFastUpwardTones);
    //while(bSoundActive) {}
	}
  else {
    for(z = 0; z<nextEmptyCell; z++)
    {
    	//search for a previous local cell that matches the current view to a certain degree
      memcpy(localComparison,poseAssoc[z].localView,numNeuralUnits*2);
      dotTempValue = dotMultiply();
      tempAngle = acos(dotTempValue);
      if(tempAngle<0.26)//0.17 //if difference less than 10 degrees between vectors
      {
      	datalogging2(z);
      	match = 1;
      	break; //save cycles break out
      }
    }
    if(match == 0)
    {//no match found - create a new local view cell
    	addAssociation(nextEmptyCell);
    	datalogging2(nextEmptyCell);
    	nextEmptyCell++;
    	nxtDisplayCenteredTextLine(6, "cell created");
      //PlaySound(soundFastUpwardTones);
      //while(bSoundActive) {}
    }
    else if(match == 1)
    {
      //PlaySound(soundBeepBeep);
      //while(bSoundActive) {}
    }
  }
}

//----Set direction and theta if turning----//
void handleDirection(char turn)
{
	switch (turn)
	{
	  case 'l':
	    if(currentDirection == 0)
	    {
	      currentDirection = 1;
	    	currentTheta = 90;
	    }
		  else if(currentDirection == 1)
		  {
		    currentDirection = 2;
		  	currentTheta = 180;
		  }
		  else if(currentDirection == 2)
		  {
		  	currentDirection = 3;
		  	currentTheta = 270;
		  }
		  else if(currentDirection == 3)
		  {
		  	currentDirection = 0;
		  	currentTheta = 0;
		  }
		  break;
		 case 'r':
	    if(currentDirection == 0)
	    {
	      currentDirection = 3;
	    	currentTheta = 270;
	    }
		  else if(currentDirection == 1)
		  {
		    currentDirection = 0;
		  	currentTheta = 0;
		  }
		  else if(currentDirection == 2)
		  {
		  	currentDirection = 1;
		  	currentTheta = 90;
		  }
		  else if(currentDirection == 3)
		  {
		  	currentDirection = 2;
		  	currentTheta = 180;
		  }
		  break;
		  case 'b':
	    if(currentDirection == 0)
	    {
	      currentDirection = 2;
	    	currentTheta = 180;
	    }
		  else if(currentDirection == 1)
		  {
		    currentDirection = 3;
		  	currentTheta = 270;
		  }
		  else if(currentDirection == 2)
		  {
		  	currentDirection = 0;
		  	currentTheta = 0;
		  }
		  else if(currentDirection == 3)
		  {
		  	currentDirection = 1;
		  	currentTheta = 90;
		  }
		  break;
		 default: break;
	}
}


//----Turns if need to----//
void doTurn()
{
//part of the testing reigme of the local cells
	//decided that anticlockwise is positive
	int rightSonarValue = SensorValue(rightSonar); //obvious
  int leftSonarValue = SensorValue(leftSonar);
  int centreSonarValue = SensorValue(centreSonar);


	if(centreSonarValue<19)
	{
	  if(leftSonarValue > 19 && rightSonarValue < 19)
	  {

	  	nSyncedTurnRatio = 100;
	  	nMotorEncoderTarget[motorB] = 190;
	    motor[motorB] = -50;
	    while(nMotorRunState[motorB] != runStateIdle) {}
	    nSyncedTurnRatio = -100;
	  	nMotorEncoderTarget[motorB] = 190;
	    motor[motorB] = -50;
	    while(nMotorRunState[motorB] != runStateIdle) {}
	    handleDirection('l');
	  }
		else if(leftSonarValue < 19 && rightSonarValue > 19)
	  {
	  	nSyncedTurnRatio = 100;
	  	nMotorEncoderTarget[motorB] = 190;
	    motor[motorB] = -50;
	    while(nMotorRunState[motorB] != runStateIdle) {}
	    nSyncedTurnRatio = -100;
	  	nMotorEncoderTarget[motorB] = 190;
	    motor[motorB] = 50;
	    while(nMotorRunState[motorB] != runStateIdle) {}
	    handleDirection('r');
	  }
		else if(leftSonarValue < 19 && rightSonarValue < 19)
	  {
	  	nSyncedTurnRatio = 100;
	  	nMotorEncoderTarget[motorB] = 190;
	    motor[motorB] = -50;
	    while(nMotorRunState[motorB] != runStateIdle) {}
	    nSyncedTurnRatio = -100;
	  	nMotorEncoderTarget[motorB] = 370;
	    motor[motorB] = 50;
	    while(nMotorRunState[motorB] != runStateIdle) {}
      handleDirection('b');
	   }
	  else
	  {
	  	nSyncedTurnRatio = 100;
	  	nMotorEncoderTarget[motorB] = 190;
	    motor[motorB] = -50;
	    while(nMotorRunState[motorB] != runStateIdle) {}
	  	nSyncedTurnRatio = -100;
	  	nMotorEncoderTarget[motorB] = 190;
	    motor[motorB] = -50;
	    while(nMotorRunState[motorB] != runStateIdle) {}
      handleDirection('l');
	  }
  }
}

//----main----//
task main ()
{
	nMaxRegulatedSpeedNxt = 750;
	nDatalogSize = 6000;
	clearLocal();
	nxtDisplayCenteredTextLine(3, "Roaming");
	nxtDisplayCenteredTextLine(5, "This is a test");
	currentDirection = 0; //set initial
  currentTheta = 0;
  setTemp();  //get local view
  checkLocalCell(); //create first association
  char numLoops = 0;
  int motorBError = 0;
  int motorCError = 0;
  int step1 = 160;
  int step2 = 123;
	while(numLoops < 2)
	{

	nSyncedMotors = synchNone;
  nMotorEncoder[motorB] = 0;
  nMotorEncoder[motorC] = 0;
  motor[motorC] = 0;
	nSyncedMotors = synchBC;
	nSyncedTurnRatio = 40;
	nMotorPIDSpeedCtrl[motorB] = mtrEncoderReg;
	nMotorPIDSpeedCtrl[motorC] = mtrSyncRegMaster;



  nMotorEncoderTarget[motorB] = 3980;
  motor[motorB] = 60;
  while(nMotorRunState[motorB] != runStateIdle){

	setTemp();
  checkLocalCell();
  }


  eraseDisplay();
  nxtDisplayCenteredBigTextLine(4, "%d", nMotorEncoder[motorB]);
  nxtDisplayCenteredBigTextLine(2, "%d", nMotorEncoder[motorC]);
  wait10Msec(80);


  nSyncedMotors = synchNone;
  nMotorEncoder[motorB] = 0;
  nMotorEncoder[motorC] = 0;
  motor[motorB] = 0;
  nSyncedMotors = synchCB;
	nSyncedTurnRatio = 60;
  nMotorPIDSpeedCtrl[motorC] = mtrEncoderReg;
  nMotorPIDSpeedCtrl[motorB] = mtrSyncRegMaster;
  nxtDisplayCenteredBigTextLine(4, "%d", nMotorEncoder[motorC]);
  nxtDisplayCenteredBigTextLine(2, "%d", nMotorEncoder[motorC]);
  wait10Msec(80);
  eraseDisplay();

    nMotorEncoderTarget[motorC] = 3840;
  	motor[motorC] = 40;
  	int count5 = 0;
    while(nMotorRunState[motorC] != runStateIdle)
    {
      nxtDisplayCenteredBigTextLine(3, "%d", count5);
    	setTemp();
      checkLocalCell();
      count5++;
   }
    nxtDisplayCenteredBigTextLine(3, "%d", nMotorEncoder[motorC]);


  nSyncedMotors = synchNone;
  nMotorEncoder[motorB] = 0;
  nMotorEncoder[motorC] = 0;
  motor[motorC] = 0;
  numLoops++;
  wait10Msec(20);
		/*
    while(nMotorEncoder[motorB]<6560) //7 times round circle
	  {
		  alive(); //stop NXT from sleeping
	    nSyncedMotors = synchBC;
	    nMotorPIDSpeedCtrl[motorB] = mtrEncoderReg;
      nMotorPIDSpeedCtrl[motorC] = mtrSyncRegSlave;
	    nSyncedTurnRatio = 77; //move forward
      nMotorEncoderTarget[motorB] = 160;
	    motor[motorB] =70;
      while(nMotorRunState[motorB] != runStateIdle) {}
      eraseDisplay();
		  nxtDisplayCenteredTextLine(2, "B: %6d",nMotorEncoder[motorB]);
      nxtDisplayCenteredTextLine(3, "C: %6d",nMotorEncoder[motorC]);
      setTemp();
      checkLocalCell();
      motorBError = nMotorEncoder[motorB] - step1;

      motorCError = nMotorEncoder[motorC] - step2;

      nxtDisplayCenteredTextLine(4, "Berr: %6d",motorBError);
      nxtDisplayCenteredTextLine(5, "Cerr: %6d",motorCError);
      //wait10Msec(100);
      nSyncedMotors = synchNone;
      nMotorEncoderTarget[motorB] = motorBError;
      nMotorEncoderTarget[motorC] = motorCError;
      if(motorBError>0)
      {
        motor[motorB] = -15;
      }
      else if(motorBError<0)
      {
      	motor[motorB] = 15;
      }
      if(motorCError>0)
      {
      	motor[motorC] = -15;
      }
      else if(motorCError)
      {
        motor[motorC] = 15;
      }
      while(nMotorRunState[motorB] != runStateIdle || nMotorRunState[motorC] != runStateIdle) {}
      nxtDisplayCenteredTextLine(1, "Fixed");
      motorBError = nMotorEncoder[motorB] - step1;
      motorCError = nMotorEncoder[motorC] - step2;
      nxtDisplayCenteredTextLine(4, "Berr: %6d",motorBError);
      nxtDisplayCenteredTextLine(5, "Cerr: %6d",motorCError);
      wait10Msec(200);

      step1 +=160;
      step2 +=123;
     }
     nSyncedMotors = synchNone;
     nMotorEncoder[motorB] = 0;
     nMotorEncoder[motorC] = 0;
     motorBError = 0;
     motorCError = 0;
     step1 = 160;
     step2 = 123;

     while(nMotorEncoder[motorB]<6560)
     {
       //eraseDisplay();

       nMotorPIDSpeedCtrl[motorB] = mtrEncoderReg;
       nMotorPIDSpeedCtrl[motorC] = mtrSyncRegSlave;
	     nSyncedMotors = synchCB;
	     nSyncedTurnRatio = 77; //move forward
       nMotorEncoderTarget[motorC] = 160;
	     motor[motorC] =70;
       while(nMotorRunState[motorC] != runStateIdle) {}
       nxtDisplayCenteredTextLine(2, "B: %6d",nMotorEncoder[motorB]);
       nxtDisplayCenteredTextLine(3, "C: %6d",nMotorEncoder[motorC]);
       setTemp();
       checkLocalCell();
       motorBError = nMotorEncoder[motorB] - step2;
       motorCError = nMotorEncoder[motorC] - step1;
      // wait10Msec(100);
        nxtDisplayCenteredTextLine(4, "Berr: %6d",motorBError);
      nxtDisplayCenteredTextLine(5, "Cerr: %6d",motorCError);
      //wait10Msec(100);
      nSyncedMotors = synchNone;
      nMotorEncoderTarget[motorB] = motorBError;
      nMotorEncoderTarget[motorC] = motorCError;
      if(motorBError>0)
      {
        motor[motorB] = -15;
      }
      else if(motorBError<0)
      {
      	motor[motorB] = 15;
      }
      if(motorCError>0)
      {
      	motor[motorC] = -15;
      }
      else if(motorCError)
      {
        motor[motorC] = 15;
      }
      while(nMotorRunState[motorB] != runStateIdle || nMotorRunState[motorC] != runStateIdle) {}
      step1 +=180;
      step2 +=90;
       }

    //doTurn();
     nSyncedMotors = synchNone;
     nMotorEncoder[motorB] = 0;
     nMotorEncoder[motorC] = 0;
     motorBError = 0;
     motorCError = 0;
     step1 = 180;
     step2 = 90;
     */
  }
    SaveNxtDatalog();

}
