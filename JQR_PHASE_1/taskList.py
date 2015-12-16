#! usr/bin/

import sys
import random
import string

JQRTask = {1: ["TASK 1: Add {} to number {}.", "INT:2"],
           2: ["TASK 2: Divide {} by {}.", "INT:2"],
           3: ["TASK 3: Multiply {} by {}.", "INT:2"],
           4: ["TASK 4: Subtract {} from {}.", "INT:2"],
           5: ["TASK 5: What is the remainder of {} divided by {}.", "INT:2"],
           6: ["TASK 6: Generate {} battle ship boards with the following dimensions {}x{}", "INT:3"],
           7: ["TASK 7: Fire a round at you battleship BOARD0 with corrdinates {}x{}", "INT:2"]}, 



def GetTaskArgs(taskNum, currIndex, maxValue = 5000, minValue = 1, nRows = 0, nCols = 0):
    argType = JQRTask[taskNum][currIndex].split(':')[0]
    numArgs = int(JQRTask[taskNum][currIndex].split(':')[1])

    _args = []
    while (len(_args) < numArgs):
        if (argType == "INT"):
            
            if( taskNum == 7):
                value = random.randrange(nRows)
                _args.append(value)
                value = random.randrange(nCols)
                _args.append(value)
                return _args
            value = random.randrange(maxValue - minValue) + minValue
            _args.append(value)
        elif (argType == "FLOAT"):
            _args.append(random.uniform(maxValue - minValue) + minValue)
        elif (argType == "STR"):
            chars = string.ascii_uppercase + string.digits
            genString = ''
            numChars = int(JQRTask[taskNum][currIndex].split(':')[2])
            for character in numChars:
                genString.join(random(chars))
                _args.append(''.join(random(chars)))
        elif (argType == "CHAR"):
            _args.append(string.ascii_uppercase + string.digits)
    return _args

def GetArgsInFmtString(data):
    #Get the length of data since we can have multiple data types avaliable
    _lenOfData = len(data)
    _dataArray = []
    _currIndex = 0

    #Since our task organizes data in a list for each data type we must
    #combine it into one array to make the printing of the string more stream lined
    while _currIndex < _lenOfData:
        _dataIndex = 0
        while _dataIndex < len(data[_currIndex]):
            _dataArray.append(data[_currIndex][_dataIndex])
            _dataIndex += 1

        _currIndex += 1
    return _dataArray

def GetTaskString(taskNum, data):

    #Get the length of data since we can have multiple data types avaliable
    _lenOfData = len(data)
    _dataArray =  GetArgsInFmtString(data)

    _lenFmtStr = len(_dataArray)

    TaskMsg = ''
    if (_lenFmtStr== 1):
        TaskMsg = JQRTask[taskNum][0].format(_dataArray[0])
    elif (_lenFmtStr == 2):
        TaskMsg = JQRTask[taskNum][0].format(_dataArray[0], _dataArray[1])
    elif (_lenFmtStr == 3):
        TaskMsg = JQRTask[taskNum][0].format(_dataArray[0], _dataArray[1], _dataArray[2])
    elif (_lenFmtStr == 4):
        TaskMsg = JQRTask[taskNum][0].format(_dataArray[0], _dataArray[1], _dataArray[2], _dataArray[3])
    elif (_lenFmtStr == 5):
        TaskMsg = JQRTask[taskNum][0].format(_dataArray[0], _dataArray[1], _dataArray[2], _dataArray[3], _dataArray[4])
    elif (_lenFmtStr == 6):
        TaskMsg = JQRTask[taskNum][0].format(_dataArray[0], _dataArray[1], _dataArray[2], _dataArray[3], _dataArray[4], _dataArray[5])

    return TaskMsg

def GetTask(taskNum, maxValue = 5000, minValue = 1, nRows =  0, nCols = 0):
    retVal = {"TASKMSG": "", "TASKDATA": '', "EXPECTEDRESLUT": ''}
    _numElements = len(JQRTask[taskNum])
    _data = []
    _currIndex = 1
    while (_currIndex < _numElements):
        _data.append(GetTaskArgs(taskNum, _currIndex, maxValue, minValue, nRows, nCols))
        _currIndex = _currIndex + 1

    retVal["TASKMSG"] = GetTaskString(taskNum, _data)
    retVal["TASKDATA"] = GetArgsInFmtString(_data)
    retVal['EXPECTEDRESLUT'] = 0
    return retVal

def getBoardDimesions(boardName):
    retVal = {'ROWS': -1, 'COLS': -1}
    gameBoard = open(boardName, "r")

    lines =  gameBoard.readlines()
    retVal['ROWS'] = len(lines)
    retVal['COLS'] = len(lines[0])
    gameBoard.close()

    return retVal