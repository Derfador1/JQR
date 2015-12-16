import socket
import sys
from JQRSolutions import getResult


class JQRClient: 

    def __init__(self, HOST, PORT):

        self.data = " ".join(sys.argv[1:])
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.sock.connect((HOST, PORT))  # Connect to server and send data
        except:
            self.sock.close()
    
    
    def Login(self):
        retVal = { "MSG": '', "STATUS": "FAIL", "RETCODE": -1}
        #Title plus user name
        self.data = str(self.sock.recv(1024), "utf-8")
        print("{}". format(self.data))

        self.data = input("User Name: _________\b\b\b\b\b")
        self.sock.sendall(bytes(self.data + "\n", "utf-8"))


        #Password
        self.data = str(self.sock.recv(1024), "utf-8")
        self.data = input("Password: _________\b\b\b\b\b")
        self.sock.sendall(bytes(self.data + "\n", "utf-8"))

        #Get success or fail
        retVal['STATUS'] = self.sock.recv(1024).decode("utf-8")
        print(retVal['STATUS'])

        if (retVal['STATUS'] == "SUCCESS"):
            print( "Connection complete begin task processing\n")
            self.sock.sendall(bytes(retVal['STATUS'], "utf-8"))
        else: 
            print( "Connection failed invalid password/user name\n")            
            self.sendall(bytes(retVal['STATUS'], "utf-8"))

        return retVal

    def getTaskMessage(self):
        retVal = { "MSG": '', "STATUS": "FAIL", "RETCODE": -1, "TASKDATA": 0}
        numBytesRecv = int.from_bytes(self.sock.recv(4), byteorder='big')
        if(numBytesRecv == 0):
            retVal['MSG']       = "NO TASK MESSGE SENT"
            retVal['STATUS']    = "SUCCESS"
            retVal['RETCODE']   = -2
        received = self.sock.recv(numBytesRecv)

        #get the Task Message
        try:
           retVal['MSG'] = received.decode("utf-8").strip()
        except Exception as e:
            print("GET MESSAFE FAILED: {}".format(received))
            return retVal

        if retVal['MSG'] == '':
            print("NO TASK RECEVED: CHECK SERVER TO ENSURE JQR IS COMPLETE.")
            retVal['RETCODE'] = -1
            return retVal
        
        print("TASK MESSAGE: {}".format(retVal['MSG']))
        retVal['STATUS'] = "SUCCESS"
        retVal['RETCODE'] = 0
        return retVal

    def getTaskData(self):
        retVal = { "MSG": '', "STATUS": "FAIL", "RETCODE": -1, 'TASKDATA': 0}

        numElements = int.from_bytes(self.sock.recv(4), byteorder='big')
        taskData = []
        while len(taskData) < numElements:
              data = int.from_bytes(self.sock.recv(4), byteorder='big')
              taskData.append(data)

        if (len(taskData) == 0):
           self.retVal['MSG'] = "FAILED TO RECEIVE TASKDATA"
           return self.retVal

        print("TASK DATA RECEIVED: {}".format(taskData))
        retVal['TASKDATA'] = taskData
        retVal['MSG'] = "Data received"
        retVal['RETCODE'] = 0
        retVal['STATUS'] = 0

        return retVal

    def sendAndValidateAnswer(self, taskNum, data):
        retVal = { "MSG": '', "STATUS": "FAIL", "RETCODE": -1, "TASKDATA": 0}
        response = self.generateAnswer(taskNum, data)
        
        if response["STATUS"] == "FAIL":
           retVal["MSG"] = "FAILED TO GENERATE AN ANSWER"
           return retVal

        answer = response["ANSWER"]

        print("SENDING ANSWER OF: {}".format(answer))
        if( (taskNum == 6) or (taskNum == 7)):
            self.sock.sendall(bytes(answer, "utf-8"))
        else:
            answer = float.hex(answer)
            self.sock.sendall(bytes(answer, "utf-8"))

        #Check Success or fail
        received = self.sock.recv(1024)
        try:
           received = received.decode("utf-8")
        except Exception as e:
            print(received)
            return retVal

        retVal['STATUS'] = received
        print("RESPONSE: {}".format(received))        
        if(retVal['STATUS']   == "FAIL"):
            retVal['MSG']     = "INCORRECT ANSWER GENERATED"
            retVal['RETCODE'] = -1
        
        elif(retVal['STATUS'] == "SUCCESS"):
            retVal['MSG']     = "CORRECT ANSWER GENERATED"
            retVal['RETCODE'] = 0

        return retVal

    def generateAnswer(self, taskNum, data):
        retVal = { "MSG": '', "STATUS": "FAIL", "RETCODE": -1, "ANSWER": ''}
        print("DATA IS: {}".format(data))
        retVal["ANSWER"] = getResult(taskNum, data)
        
        if retVal["ANSWER"] == "FAIL":
            retVal["MSG"] = "FAILED TO GENERATE ANSWER"
            print("FAILED GET RESULT")
            return retVal

        retVal["STATUS"] = "SUCCESS"
        retVal["MSG"]    = "ANSWER GENERATED"
        retVal["RETCOE"] = 0
        return retVal

    def processTask(self):
        self.retVal = {"MSG": '', "STATUS": "FAIL", "RETCODE": -1, "TASKDATA": 0}

        taskNum = 1
        while self.data != 'exit':

            print("--------------------------------")
            self.retVal = self.getTaskMessage()
            if((self.retVal['STATUS'] == "FAIL") or (self.retVal['RETCODE'] == -1)):
                return

            self.retVal = self.getTaskData()
            if(self.retVal['STATUS'] == "FAIL"):
                print(self.retVal['MSG'])
                continue

            self.retVal = self.sendAndValidateAnswer(taskNum, self.retVal['TASKDATA'])
            if(self.retVal['STATUS'] == "FAIL"):
                continue

            self.retVal['STATUS'] = "FAIL"
            self.retVal['MSG'] = ""
            self.retVal['RETCODE'] = -1
            taskNum += 1

        return



if __name__ == "__main__":
    HOST, PORT = "localhost", int(sys.argv[1])
    client = JQRClient(HOST, PORT)
    if(client.Login()['STATUS'] == "SUCCESS"):
       client.processTask()
    else:
        print("CLOSING CLIENT")
