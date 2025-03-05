"""
Author      :       Ganapati Kundapura
Date        :       October 2022
Environment :       Windows 11
Version     :       Python 3.8.10
To execute  :       mpiexec -n 4 python3 suzuki_kasami.py
"""


import sys
import random
import threading
from time import sleep
from mpi4py import MPI
from threading import Thread
from collections import deque
from colorama import init, Fore, Style

# Initialize MPI
comm = MPI.COMM_WORLD
threadId = comm.Get_rank()
numberofProcess = comm.Get_size()

# Token queue
tokenQueue = deque()

# having token: 1, otherwise: 0
hasToken = 0

# entered critical secion = 1, otherwise: 0
inCriticalSection = 0

# Requested for token = 1, otherwise: 0
reqForToken = 0

# Synchronization lock for each step
criticalSectionLock = threading.Lock()
sendTokenLock = threading.Lock()
rnLock = threading.Lock()
releaseLock = threading.Lock()

# Only one process can request for the token at one time
requestLock = threading.Lock()
# Only one process can have the token at one time
tokenLock = threading.Lock()
initLock = threading.Lock()

# List for keeping information about most recent sequence execution by a site in the token
LN = [0]*numberofProcess

# List for keeping the largest sequence number of request from a site
RN = [0]*numberofProcess

# Method for ensuring mutual exclusion during token request
def requestToken():
    global hasToken
    global RN
    global inCriticalSection
    global reqForToken
    with requestLock:
        '''
        if site doesn't have token, then
        Inrement Request array RN[siteId]
        send (siteId, seqNum) to all sites
        '''
        if hasToken == 0:
            RN[threadId] += 1
            currentValue = RN[threadId]
            print("[REQ-TOKEN] %d wants to request for a token to enter CS." % threadId)
            sys.stdout.flush()
            reqForToken = 1
            startSend(currentValue)

# Method for sending requests to other sites
def startSend(value):
    for i in range(numberofProcess):
        if threadId != i:
            print("[REQ-TOKEN] %d sends request(%d, %d) to %d!!!" % (threadId, threadId, threadId, i))
            sys.stdout.flush()
            valueSent = ['CS', threadId, value]
            comm.send(valueSent, dest=i)
            sleep(2)

# Method for sending token to another site
def sendToken(receiver):
    global tokenQueue
    global inCriticalSection
    with sendTokenLock:
        print("[REQ-TOKEN] %d sends token(%s, %s) to %d." %
              (threadId, str(tokenQueue), str(LN), receiver))
        sys.stdout.flush()
        token = ['Token', LN, tokenQueue]
        comm.send(token, dest=receiver)

# Method that does processing related to receiving a message form a site
def receive():
    global LN
    global reqForToken
    global hasToken
    global RN
    global tokenQueue
    global inCriticalSection
    while True:
        message = comm.recv(source=MPI.ANY_SOURCE)

        # Receives a request
        if message[0] == 'Init':
            with initLock:
                RN[message[1]] = message[2]
                #print(f"RN({threadId}) = {RN}")
                #sys.stdout.flush()
                sleep(2)

        if message[0] == 'CS':
            with rnLock:
                print("[REQ-RCVD] %d received request(%d, %d) from %d." %
                     (threadId, message[1], message[2], message[1]))

                RN[message[1]] = max([message[2], RN[message[1]]])
                print(Fore.CYAN + "Updated RN(%d) = %s." %
                     (threadId, str(RN)))
                sys.stdout.flush()

                # Check for out of date requests
                if message[2] < RN[message[1]]:
                    print("[OUTDATED-REQ] Request from %d is out of date." %
                          message[1])
                    sys.stdout.flush()
                # If process j has token, no other process is in cs and RN[i] = LN[i]+1 then send token
                if (hasToken == 1) and inCriticalSection == 0 and (RN[message[1]] == (LN[message[1]] + 1)):
                    hasToken = 0
                    sendToken(message[1])
                    
        # Receives a token
        elif message[0] == 'Token':
            with tokenLock:
                print("[TOKEN-RCVD] %d receives a token(%s, %s)." %
                      (threadId, str(message[2]), str(message[1])))
                sys.stdout.flush()
                hasToken = 1
                reqForToken = 0
                LN = message[1]
                tokenQueue = message[2]
                print(Fore.CYAN + "Updated tokenQueue = %s, LN = %s" %
                     (str(tokenQueue), str(LN)))
                enterCriticalSection()

# Method that is used to enter critical section
def enterCriticalSection():
    global inCriticalSection
    global hasToken
    with criticalSectionLock:
        '''
        site on receiging the token enters CS
        '''
        if hasToken == 1:
            inCriticalSection = 1
            print("[ENTER-CS] %d received token and enters CS.\n" %
                  threadId)
            sys.stdout.flush()
            sleep(random.uniform(3, 7))
            print("[EXIT-CS] %d finishes CS.\n" % threadId)
            sys.stdout.flush()
            inCriticalSection = 0
            exitCriticalSection()

# Method that is used to exit critical section
def exitCriticalSection():
    global inCriticalSection
    global LN
    global RN
    global tokenQueue
    global hasToken
    with releaseLock:
        # set LN[siteId] = RN[siteId]
        LN[threadId] = RN[threadId]
        '''
        For every site, whose ID is not in tokenQueue
        append it's sitID to tokenQueue if RN[siteId] == (LN[siteId] + 1)
        '''
        for i in range(numberofProcess):
            if i not in tokenQueue:
                if RN[i] == (LN[i] + 1):
                    tokenQueue.append(i)
                    print("[TOKENQ-UPDATE] %d has added %d to the queue. Now queue of token is: %s." % 
                          (threadId, i, str(tokenQueue)))
                    sys.stdout.flush()

        '''
        if tokenQue is non-emptry after the above update,
        delete the top site ID from the tokenQue
        send the token to the site indicated by ID
        '''
        if tokenQueue:
            hasToken = 0
            print("[TOKENQ-UPDATE] %d removes %d from tokenQueue = %s." % 
                  (threadId, tokenQueue[0], str(tokenQueue)))
            sendToken(tokenQueue.popleft())


# Main program module that starts the communication in an infinite loop (the communication must be terminated manually!)
if __name__ == "__main__":

    #Enable autoreset for foreground color
    init(autoreset=True)

    # python version check
    if not sys.version_info.major <= 3 and sys.version_info.minor < 8:
        print(Fore.RED + "Python 3.8 or higher version is required.")
        print(Fore.RED + "This code is tested in python %d.%d.%d" %
             (sys.version_info.major, sys.version_info.minor, sys.version_info.micro))
        sys.exit(1)

    #Enable autoreset for foreground color
    init(autoreset=True)

    # Assume Process 0 has token initially
    if threadId == 0:
        print("[INIT] %d has a token initially." % threadId)
        hasToken = 1
        RN[threadId] = 1

        for i in range(numberofProcess):
            if threadId != i:
                valueSent = ['Init', threadId, 1]
                comm.send(valueSent, dest=i)
                #sleep(3)


    # send request array to all sites
    with initLock:
        if threadId == 0:
            for i in range(numberofProcess):
                #print(f"Initial RN({i}) = {RN}")
                print(Fore.CYAN + "[INIT] Initial RN(%d) = %s" % (i, str(RN)))
            print('\n')

    try:
        threadSource = Thread(target=receive)
        threadSource.start()
    except:
        print("[ERROR] Error during thread creation!")

    while True:
        if hasToken == 0:
            sleep(random.uniform(1, 3.5))
            requestToken()
        elif inCriticalSection == 0:
            enterCriticalSection()

        while reqForToken:
            sleep(random.uniform(1, 3))

