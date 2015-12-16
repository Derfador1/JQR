#! usr/bin/

import JQRSolution as Sol
import socketserver
from taskList import JQRTask
from taskList import GetTask
from taskList import getBoardDimesions
from sys import argv
from taskList import getBoardDimesions

def getServerResult(taskNum, data):
    if taskNum == 1:
        return Sol.AddTwoNumbers(data[0], data[1])
    elif taskNum == 2:
        return Sol.DivideTwoNumbers(data[0], data[1])
    elif taskNum == 3:
        return Sol.MultiplyTwoNumbers(data[0], data[1])
    elif taskNum == 4:
        return Sol.SubtractTwoNumbers(data[0], data[1])
    elif taskNum == 5:
        return Sol.GetRemainder(data[0], data[1])
    elif taskNum == 6:
        for boardCount in range(0, data[0]):
            retVal = Sol.GenerateBoard(data[1], data[2], "./Boards/BOARD"+str(boardCount))
            if (retVal == -1):
                print("FAILED TO GENERATE BOARD {}".format(boardCount))
                return "FAIL"
        return "SUCCESS"
    elif taskNum == 7: 
        retVal = Sol.FireRound(data[0], data[1], getBoardDimesions("./Boards/BOARD0")['COLS'], "./Boards/BOARD0")
        if retVal == 1:
            return "FIRED SHOT HIT"
        elif retVal == 0:
            return "FIRED: SHOT MISSED"
        elif retVal == -1:
            return "FAILED TO FIRE IN MODULE"
        else:
            return "FAIL"



class JQRTCPHandler(socketserver.BaseRequestHandler):
    """
    The RequestHandler class for our server.

    It is instantiated once per connection to the server, and must
    override the handle() method to implement communication to the
    client.K
    """
    def login(self): 

        print("Sending Welcome Screen\n")
        self.request.sendall(bytes("Welcome to the JQR Server\n", "utf-8"))

        print("Getting user ID")
        self.request.send(bytes("Please enter a user name", "utf-8"))
        userName = self.request.recv(1024).decode("utf-8").upper().strip()


        print("Getting Password")
        self.request.send(bytes("Please enter a password", "utf-8"))
        userPass = self.request.recv(1024).decode("utf-8").upper().strip()


        self.STATUS = "FAIL"
        if ((str(userName) == "BOB") and
            (str(userPass) == "BOB")):
               print("In the check for user name\n")
               self.STATUS = "SUCCESS"

        print("SENDING STATUS BACK TO CLIENT")
        self.request.sendall(bytes(self.STATUS, "utf-8"))
        print("User ID: {} \tpassword: {} \tStatus: {}".format(userName, userPass, self.STATUS))
        data = self.request.recv(1024).decode("utf-8")

        print("CONFORMATION FROM CLIENT: {}".format(data))
        return data

    def getResponse(self, taskNum):
        if ((taskNum == 6) or (taskNum == 7)):
          self.data = self.request.recv(1024).decode("utf-8")
        else:
          self.data = float.fromhex(self.request.recv(1024).decode("utf-8"))
        return self.data

    def processTask(self, taskNum, maxValue = 1, minValue = 1, nRows = 0, nCols = 0):
        retVal = { "TASKMSG": "", "TASKDATA": '', "EXPECTEDRESLUT":  ''}
        RowAndCol = getBoardDimesions("./Boards/BOARD0")
        print("ROWS: {} COLS: {}".format(nRows, nCols))
        retVal = GetTask(taskNum, maxValue, minValue, RowAndCol['ROWS'], RowAndCol['COLS'])
        print(retVal["TASKMSG"])
        return retVal

    def sendTaskMessage(self, Message):
        retVal = { "STATUS": "FAIL", "RETCODE": -1}
        self.request.sendall(len(Message).to_bytes(4, byteorder='big'))
        self.request.sendall(bytes(Message, "utf-8"))
        return retVal

    def validateResponse(self, taskNum, taskData):
        print("AWAITING RESPONSE FOR TASK: {}".format(taskNum))
        response = self.getResponse(taskNum)
        print("RESPONSE: {}".format(response))

        expectedResult = getServerResult(taskNum, taskData)
        print("EXPECTED RESULT: {}".format(expectedResult))

        if(expectedResult != response):
            print("TASK {} FAILED: SENDING FAILURE MESSAGE".format(taskNum))
            self.request.sendall(bytes("FAIL", "utf-8"))
            return "FAIL"
        else:
            print("TASK {} PASSED: SENDING SUCCESS MESSAGE".format(taskNum))
            self.request.sendall(bytes("SUCCESS", "utf-8"))
            return "SUCCESS"

    def sendTaskData(self, taskNum, taskData):

        retVal = { "STATUS": "FAIL", "RETCODE": -1}

        #Get the total num of data elements
        currElement = 0
        print("SENDING TOTAL NUMBER OF ELEMENTS: {}".format(len(taskData)))
        self.request.sendall(len(taskData).to_bytes(4, byteorder='big'))


        currIndex = 1
        while currIndex < len(JQRTask[taskNum]):
           dataType = JQRTask[taskNum][currIndex].split(':')[0]
           numArgs = int(JQRTask[taskNum][currIndex].split(':')[1])

           argCount = 0
           while argCount < numArgs:
              if (dataType == 'INT'):
                  self.request.sendall(taskData[currElement].to_bytes(4, byteorder='big'))
              elif (dataType == 'UINT'):
                  self.request.sendall(taskData[currElement].to_bytes(4, byteorder='big'))
              elif (dataType == 'FLOAT'):
                  continue

              elif (dataType == 'STR'):
                  continue

              else:
                  print("Received unhandled data type\n")

              argCount += 1
              currElement += 1
           currIndex += 1

           return retVal

    def handle(self):
        retVal = { "TASKMSG": "", "TASKDATA": ''}
        failedTask = 0

        result = self.login()

        if( result == "SUCCESS"):
          
          #Send task to client
           for taskNum in range(1, len(JQRTask)+1):
               print("----------------------------")
               print ("SEND TASK {} of {}".format(taskNum, len(JQRTask)))
               
               if taskNum == 6: 
                  retVal = self.processTask(taskNum, 25, 10)
               elif taskNum == 7: 
                   RowAndCol = {'ROWS': -1, 'COLS': -1}
                   RowAndCol = getBoardDimesions("./Boards/BOARD0")
                   retVal = self.processTask(taskNum, 5000,1, RowAndCol['ROWS'], RowAndCol['COLS'])
               else:
                  retVal = self.processTask(taskNum, 5000, 1)

               self.sendTaskMessage(retVal['TASKMSG'])
               self.sendTaskData(taskNum, retVal['TASKDATA'])
               if(self.validateResponse(taskNum, retVal['TASKDATA']) == "FAIL"):
                   failedTask += 1
          
           print("----------------------------")
           print("JQR COMPLETE")
        return

if __name__ == "__main__":
    HOST, PORT = "localhost", int(argv[1])

    # Create the server, binding to localhost on port 9999
    server = socketserver.TCPServer((HOST, PORT), JQRTCPHandler)
    print("Listening on port {}".format(PORT))
    try:
       server.serve_forever()
       server.shutdown()
    except:
       server.shutdown()
