#pragma config(Sensor, S1,     leftSonar,           sensorSONAR)
#pragma config(Sensor, S2,     centreSonar,         sensorSONAR)
#pragma config(Sensor, S3,     rightSonar,          sensorSONAR)
#pragma config(Motor,  motorB,          leftMotor,            tmotorNxtEncoderClosedLoop)
#pragma config(Motor,  motorC,          rightMotor,           tmotorNxtEncoderClosedLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      Title:- Pose Cells
//      Author:- Lachlan Smith (RobotC)
//               Mark Wakabayashi (Jave version)
//               Michael Milford (original algorithim/c code)
//      Purpose:- This is implementing pose cells and local cell together
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//----include files----//
#include "localNeural.h";
typedef struct
{
  float localView[numNeuralUnits];
  int numMatches;
} localHolder;


//----General In-Module Variables----//
int numActive = 0; //number of active cells
int currentTheta = 0; //theta for pose and turns
char currentDirection = 0; //direction for pose and turns
float localTemp[numNeuralUnits]; //holds the temporary neural value
float localComparison[numNeuralUnits]; //what the local cell data is loaded into
char nextEmptyCell = 0; //used for holding the next empty cell in the localcell Struct
localHolder poseAssoc[numLocalCells];

//                           //
//----Pose Cell Functions----//
//                           //


//                            //
//----Local View Functions----//
//                            //

//----Initialises the arrays to zero----//
void clearTemp()
{
  memset(localTemp, 0, 4*numNeuralUnits); //sets entire array to zero
  memset(localComparison, 0, 4*numNeuralUnits); //sets entire array to zero
}

void datalogging2()
{
	float time = (float) nPgmTime / 1000;
	int time2 = (int) time;
	AddToDatalog(1, time2);
  AddToDatalog(2,nextEmptyCell);
}


void clearLocal()
{
	memset(poseAssoc, 0, 2960);
}

//----Set the right neural units----//
void setRight(float rightSonarValue)
{
	//This function allocates a proportion to each neural unit based on the value returned by the sonar sensor
	//rightSonarValue = SensorValue(rightSonar);
	float tempCalc = 0;
	if(rightSonarValue <= firstUnit)
	{
		tempCalc = (float) (((firstUnit - rightSonarValue)/firstUnit));
    localTemp[12] = (float) 1 - tempCalc;
	}
  else if(rightSonarValue > firstUnit && rightSonarValue <= secondUnit)
  {
  	tempCalc = (float) (secondUnit - rightSonarValue)/(secondUnit - firstUnit);
    localTemp[12] = tempCalc;
  	localTemp[13] = 1 - tempCalc;
  }
  else if(rightSonarValue > secondUnit && rightSonarValue <= thirdUnit)
  {
  	tempCalc = (float) (thirdUnit - rightSonarValue)/(thirdUnit - secondUnit);
    localTemp[13] = tempCalc;
  	localTemp[14] = 1 - tempCalc;
  }
  else if(rightSonarValue > thirdUnit && rightSonarValue <= fourthUnit)
  {
  	tempCalc = (float) (fourthUnit - rightSonarValue)/(fourthUnit - thirdUnit);
    localTemp[14] = tempCalc;
  	localTemp[15] = 1 - tempCalc;
  }
  else if(rightSonarValue > fourthUnit && rightSonarValue <= fifthUnit)
  {
  	tempCalc = (float) (fifthUnit - rightSonarValue)/(fifthUnit - fourthUnit);
    localTemp[15] = tempCalc;
  	localTemp[16] = 1 - tempCalc;
  }
  else if(rightSonarValue > fifthUnit && rightSonarValue <= sixthUnit)
  {
  	tempCalc = (float) (sixthUnit - rightSonarValue)/(sixthUnit - fifthUnit);
    localTemp[16] = tempCalc;
  	localTemp[17] = 1 - tempCalc;
  }
  else if(rightSonarValue > sixthUnit) //if greater than 195cm
  {
    localTemp[17] = 1;
  }
}

//----Set centre neural units----//
void setCentre(float centreSonarValue)
{
	//This function allocates a proportion to each neural unit based on the value returned by the sonar sensor
	//centreSonarValue = SensorValue(centreSonar);
	float tempCalc = 0;
	if(centreSonarValue <= firstUnit)
	{
		tempCalc = (float) (((firstUnit - centreSonarValue)/firstUnit));
    localTemp[6] = (float) 1 - tempCalc;
	}
  else if(centreSonarValue > firstUnit && centreSonarValue <= secondUnit)
  {
  	tempCalc = (float) (secondUnit - centreSonarValue)/(secondUnit - firstUnit);
    localTemp[6] = tempCalc;
  	localTemp[7] = 1 - tempCalc;
  }
  else if(centreSonarValue > secondUnit && centreSonarValue <= thirdUnit)
  {
  	tempCalc = (float) (thirdUnit - centreSonarValue)/(thirdUnit - secondUnit);
    localTemp[7] = tempCalc;
  	localTemp[8] = 1 - tempCalc;
  }
  else if(centreSonarValue > thirdUnit && centreSonarValue <= fourthUnit)
  {
  	tempCalc = (float) (fourthUnit - centreSonarValue)/(fourthUnit - thirdUnit);
    localTemp[8] = tempCalc;
  	localTemp[9] = 1 - tempCalc;
  }
  else if(centreSonarValue > fourthUnit && centreSonarValue <= fifthUnit)
  {
  	tempCalc = (float) (fifthUnit - centreSonarValue)/(fifthUnit - fourthUnit);
    localTemp[9] = tempCalc;
  	localTemp[10] = 1 - tempCalc;
  }
  else if(centreSonarValue > fifthUnit && centreSonarValue <= sixthUnit)
  {
  	tempCalc = (float) (sixthUnit - centreSonarValue)/(sixthUnit - fifthUnit);
    localTemp[10] = tempCalc;
  	localTemp[11] = 1 - tempCalc;
  }
  else if(centreSonarValue > sixthUnit)
  {
    localTemp[11] = 1;
  }
}

//----set left neural units----//
void setLeft(float leftSonarValue)
{
	//This function allocates a proportion to each neural unit based on the value returned by the sonar sensor
	//leftSonarValue = SensorValue(leftSonar);
	float tempCalc = 0;
	if(leftSonarValue <= firstUnit)
	{
		tempCalc = (float) (((firstUnit - leftSonarValue)/firstUnit));
    localTemp[0] = (float) 1 - tempCalc;
	}
  else if(leftSonarValue > firstUnit && leftSonarValue <= secondUnit)
  {
  	tempCalc = (float) (secondUnit - leftSonarValue)/(secondUnit - firstUnit);
    localTemp[0] = tempCalc;
  	localTemp[1] = 1 - tempCalc;
  }
  else if(leftSonarValue > secondUnit && leftSonarValue <= thirdUnit)
  {
  	tempCalc = (float) (thirdUnit - leftSonarValue)/(thirdUnit - secondUnit);
    localTemp[1] = tempCalc;
  	localTemp[2] = 1 - tempCalc;
  }
  else if(leftSonarValue > thirdUnit && leftSonarValue <= fourthUnit)
  {
  	tempCalc = (float) (fourthUnit - leftSonarValue)/(fourthUnit - thirdUnit);
    localTemp[2] = tempCalc;
  	localTemp[3] = 1 - tempCalc;
  }
  else if(leftSonarValue > fourthUnit && leftSonarValue <= fifthUnit)
  {
  	tempCalc = (float) (fifthUnit - leftSonarValue)/(fifthUnit - fourthUnit);
    localTemp[3] = tempCalc;
  	localTemp[4] = 1 - tempCalc;
  }
  else if(leftSonarValue > fifthUnit && leftSonarValue <= sixthUnit)
  {
  	tempCalc = (float) (sixthUnit - leftSonarValue)/(sixthUnit - fifthUnit);
    localTemp[4] = tempCalc;
  	localTemp[5] = 1 - tempCalc;
  }
  else if(leftSonarValue > sixthUnit)
  {
    localTemp[5] = 1;
  }
}

//---adds the association between local view and pose----//
void addAssociation(char cellNum)
{
  //creates an association between local view and pose - currently using max activated cell as the one needed but may end
	//up using estimated pose as in RAMP code

	memcpy(poseAssoc[cellNum].localView,localTemp,numNeuralUnits*4);
	/*char k;
	for(k=0; k<numNeuralUnits; k++)
	{
	  poseAssoc[cellNum].localView[k] = localTemp[k];
	}*/
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
      dotValue = dotValue + localTemp[i] * localComparison[i];
    }
  }
  return dotValue; //return the multiply
}

//----normalise the current view for processing----//
void normaliseTemp()
{
//will normalise the temp ||a|| = sqrt(a1^2 + a2^2 + a3^3)
//normalise by a/||a||
	float tempTotal = 0;
	char y;
	for(y = 0; y < numNeuralUnits; y++)
	{
		if(localTemp[y]>0) //only if over zero spend clock cycles
		{
		  tempTotal = tempTotal + localTemp[y]*localTemp[y]; //a.a
	  }
	}
	tempTotal = sqrt(tempTotal); //sqrt(a.a)
	for(y = 0; y < numNeuralUnits; y++)
	{
		if(localTemp[y]>0)
		{
	    localTemp[y] = (float) localTemp[y]/tempTotal;
	  }
	}
}

//----Gets local view and processes ready for comparison----//
void setTemp()
{
	//initalises temp, get sensor readings and sets the local temp to a normalised neural vector
  clearTemp();
  float rightSonarValue = SensorValue(rightSonar); //obvious
  float leftSonarValue = SensorValue(leftSonar);
  float centreSonarValue = SensorValue(centreSonar);
  setLeft(leftSonarValue);
	setCentre(centreSonarValue);
	setRight(rightSonarValue);
	normaliseTemp();
}

//----Checks if there is a match, add activities, else creates a new association----//
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
    datalogging2();
    PlaySound(soundFastUpwardTones);
    while(bSoundActive) {}
	}
  else {
    for(z = 0; z<nextEmptyCell; z++)
    {
    	//search for a previous local cell that matches the current view to a certain degree
      memcpy(localComparison,poseAssoc[z].localView,numNeuralUnits*4);
      dotTempValue = dotMultiply();
      tempAngle = acos(dotTempValue);
      if(tempAngle<0.17) //if difference less than 10 degrees between vectors
      {
      	match = 1;
      	break; //save cycles break out
      }
    }
    if(match == 0)
    {//no match found - create a new local view cell
    	addAssociation(nextEmptyCell);
    	nextEmptyCell++;
    	datalogging2();
    	nxtDisplayCenteredTextLine(6, "cell created");
      PlaySound(soundFastUpwardTones);
      while(bSoundActive) {}
    }
    else if(match == 1)
    {
    	poseAssoc[nextEmptyCell-1].numMatches += 1;
      PlaySound(soundBeepBeep);
      while(bSoundActive) {}
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

void datalogging()
{
	char x;
	for(x = 0; x<numLocalCells; x++)
	{
	  AddToDatalog(1,x);
    AddToDatalog(2,poseAssoc[x].numMatches);
  }
}

//----Turns if need to----//
void doTurn()
{
//part of the testing reigme of the local cells
	//decided that anticlockwise is positive
	float rightSonarValue = SensorValue(rightSonar); //obvious
  float leftSonarValue = SensorValue(leftSonar);
  float centreSonarValue = SensorValue(centreSonar);


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
	nMaxRegulatedSpeed = 750;
	nMotorPIDSpeedCtrl[motorB] = mtrEncoderReg;
	nMotorPIDSpeedCtrl[motorC] = mtrEncoderReg;
	clearLocal();
	nxtDisplayCenteredTextLine(3, "Roaming");
	nxtDisplayCenteredTextLine(5, "This is a test");
	currentDirection = 0; //set initial
  currentTheta = 0;
  setTemp();  //get local view
  checkLocalCell(); //create first association
	while(nextEmptyCell<numLocalCells)
	{
		alive(); //stop NXT from sleeping
		//eraseDisplay();
		//nxtDisplayCenteredTextLine(2, "Num Active: - %4d",numActive);
		char lastCellNum = nextEmptyCell;
		nMotorPIDSpeedCtrl[motorB] = mtrEncoderReg;
	  nMotorPIDSpeedCtrl[motorC] = mtrEncoderReg;
	  nSyncedMotors = synchBC;
	  nSyncedTurnRatio = 100; //move forward
    nMotorEncoderTarget[motorB] = 180;
	  motor[motorB] =50;
    while(nMotorRunState[motorB] != runStateIdle) {}

    setTemp();
    checkLocalCell();
    doTurn();
  }
  SaveNxtDatalog();
  PlaySound(soundException);
  while(bSoundActive){}

}