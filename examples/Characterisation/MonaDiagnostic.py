import serial
import numpy as np
import matplotlib.pyplot as plt

LMF = np.zeros((2,52))
RMF = np.zeros((2,52))
LMB = np.zeros((2,52))
RMB = np.zeros((2,52))
LMFP = np.zeros((2,52))
RMFP = np.zeros((2,52))
LMBP = np.zeros((2,52))
RMBP = np.zeros((2,52))
MonaResults = np.zeros((10,64))

circum = 0.092 # MONA wheel circum
PulsePerRev = 980

ser = serial.Serial('/dev/tty.usbserial-DN01EOJM', 9600)

print ser.readline() # This fucntion might be unused in newer versions of PySerial? 

for i in range (0,52):
	RMF[0,i] = i*5
	LMF[0,i] = i*5
	RMFP[0,i] = i*5
	LMFP[0,i] = i*5
	MonaResults[0,i] = i*5
	print "PWM val forwards = ", i*5
	var1 = ser.readline()
	var2 = ser.readline()
	var3 = ser.readline()
	var4 = ser.readline()

	RMF[1,i] = ((float(var1))/PulsePerRev)*circum
	LMF[1,i] = ((float(var2))/PulsePerRev)*circum
	try:
		RMFP[1,i] = circum / ((float(var3)/1000000.0)*PulsePerRev)
	except ZeroDivisionError:
		RMFP[1,i] = 0

	try:
		LMFP[1,i] = circum / ((float(var4)/1000000.0)*PulsePerRev)
	except:
		LMFP[1,i] = 0

	print var1, var2, var3, var4, RMF[1,i], LMF[1,i], RMFP[1,i], LMFP[1,i]

	MonaResults[1,i] =  RMF[1,i]
	MonaResults[2,i] =  LMF[1,i]
	MonaResults[6,i] =  RMFP[1,i]
	MonaResults[7,i] =  LMFP[1,i]

for i in range (0,52):
	RMB[0,i] = i*5
	LMB[0,i] = i*5
	RMBP[0,i] = i*5
	LMBP[0,i] = i*5
	print "PWM val backwards = ", i*5
	var1 = ser.readline()
	var2 = ser.readline()
	var3 = ser.readline()
	var4 = ser.readline()
	RMB[1,i] = ((float(var1))/PulsePerRev)*circum
	LMB[1,i] = ((float(var2))/PulsePerRev)*circum
	try:
		RMBP[1,i] = circum / ((float(var3)/1000000.0)*PulsePerRev)*-1
	except ZeroDivisionError:
		RMBP[1,i] = 0

	try:
		LMBP[1,i] = circum / ((float(var4)/1000000.0)*PulsePerRev)*-1
	except:
		LMBP[1,i] = 0
	print var1, var2, var3, var4, RMB[1,i], LMB[1,i], RMBP[1,i], LMBP[1,i]
	MonaResults[3,i] =  RMB[1,i]
	MonaResults[4,i] =  LMB[1,i]
	MonaResults[8,i] =  RMBP[1,i]
	MonaResults[9,i] =  LMBP[1,i]

RightF1 = np.polyfit(RMF[1,:], RMF[0,:], 1)
LeftF1 = np.polyfit(LMF[1,:], LMF[0,:], 1)
RightB1 = np.polyfit(RMB[1,:], RMB[0,:], 1)
LeftB1 = np.polyfit(LMB[1,:], LMB[0,:], 1)
RightF2 = np.polyfit(RMF[1,:], RMF[0,:], 2)
LeftF2 = np.polyfit(LMF[1,:], LMF[0,:], 2)
RightB2 = np.polyfit(RMB[1,:], RMB[0,:], 2)
LeftB2 = np.polyfit(LMB[1,:], LMB[0,:], 2)
RightF3 = np.polyfit(RMF[1,:], RMF[0,:], 3)
LeftF3 = np.polyfit(LMF[1,:], LMF[0,:], 3)
RightB3 = np.polyfit(RMB[1,:], RMB[0,:], 3)
LeftB3 = np.polyfit(LMB[1,:], LMB[0,:], 3)


PRightF1 = np.polyfit(RMFP[1,:], RMFP[0,:], 1)
PLeftF1 = np.polyfit(LMFP[1,:], LMFP[0,:], 1)
PRightB1 = np.polyfit(RMBP[1,:], RMBP[0,:], 1)
PLeftB1 = np.polyfit(LMBP[1,:], LMBP[0,:], 1)
PRightF2 = np.polyfit(RMFP[1,:], RMFP[0,:], 2)
PLeftF2 = np.polyfit(LMFP[1,:], LMFP[0,:], 2)
PRightB2 = np.polyfit(RMBP[1,:], RMBP[0,:], 2)
PLeftB2 = np.polyfit(LMBP[1,:], LMBP[0,:], 2)
PRightF3 = np.polyfit(RMFP[1,:], RMFP[0,:], 3)
PLeftF3 = np.polyfit(LMFP[1,:], LMFP[0,:], 3)
PRightB3 = np.polyfit(RMBP[1,:], RMBP[0,:], 3)
PLeftB3 = np.polyfit(LMBP[1,:], LMBP[0,:], 3)

f1 = plt.figure()
ax1 = f1.add_subplot(111)

f2 = plt.figure()
ax2 = f2.add_subplot(111)

ax1.plot(RMF[1,:], RMF[0,:], 'bo')
ax1.plot(LMF[1,:], LMF[0,:], 'ro')
ax1.plot(RMB[1,:], RMB[0,:], 'go')
ax1.plot(LMB[1,:], LMB[0,:], 'co')

ax2.plot(RMF[1,:], RMF[0,:], 'bo')
ax2.plot(LMF[1,:], LMF[0,:], 'ro')
ax2.plot(RMB[1,:], RMB[0,:], 'go')
ax2.plot(LMB[1,:], LMB[0,:], 'co')

ax1.set_title("Velocity vs PWM char encoder ticks",fontsize=14)
ax1.set_xlabel("Velocity meters per sec",fontsize=12)
ax1.set_ylabel("PWM char 0-255",fontsize=12)

ax2.set_title("Velocity vs PWM char encoder ticks",fontsize=14)
ax2.set_xlabel("Velocity meters per sec",fontsize=12)
ax2.set_ylabel("PWM char 0-255",fontsize=12)

RightFuncF1 = np.poly1d(RightF1)
LeftFuncF1 = np.poly1d(LeftF1)
RightFuncB1 = np.poly1d(RightB1)
LeftFuncB1 = np.poly1d(LeftB1)
RightFuncF2 = np.poly1d(RightF2)
LeftFuncF2 = np.poly1d(LeftF2)
RightFuncB2 = np.poly1d(RightB2)
LeftFuncB2 = np.poly1d(LeftB2)
RightFuncF3 = np.poly1d(RightF3)
LeftFuncF3 = np.poly1d(LeftF3)
RightFuncB3 = np.poly1d(RightB3)
LeftFuncB3 = np.poly1d(LeftB3)

PRightFuncF1 = np.poly1d(PRightF1)
PLeftFuncF1 = np.poly1d(PLeftF1)
PRightFuncB1 = np.poly1d(PRightB1)
PLeftFuncB1 = np.poly1d(PLeftB1)
PRightFuncF2 = np.poly1d(PRightF2)
PLeftFuncF2 = np.poly1d(PLeftF2)
PRightFuncB2 = np.poly1d(PRightB2)
PLeftFuncB2 = np.poly1d(PLeftB2)
PRightFuncF3 = np.poly1d(PRightF3)
PLeftFuncF3 = np.poly1d(PLeftF3)
PRightFuncB3 = np.poly1d(PRightB3)
PLeftFuncB3 = np.poly1d(PLeftB3)


MonaResults[0,52] = RightFuncF2[2]
MonaResults[1,52] = RightFuncF2[1]
MonaResults[2,52] = RightFuncF2[0]
MonaResults[3,52] = LeftFuncF2[2]
MonaResults[4,52] = LeftFuncF2[1]
MonaResults[5,52] = LeftFuncF2[0]

MonaResults[0,53] = RightFuncB2[2]
MonaResults[1,53] = RightFuncB2[1]
MonaResults[2,53] = RightFuncB2[0]
MonaResults[3,53] = LeftFuncB2[2]
MonaResults[4,53] = LeftFuncB2[1]
MonaResults[5,53] = LeftFuncB2[0]

MonaResults[0,54] = RightFuncF2[2]
MonaResults[1,54] = RightFuncF2[1]
MonaResults[2,54] = RightFuncF2[0]
MonaResults[3,54] = LeftFuncF2[2]
MonaResults[4,54] = LeftFuncF2[1]
MonaResults[5,54] = LeftFuncF2[0]

MonaResults[0,55] = RightFuncB2[2]
MonaResults[1,55] = RightFuncB2[1]
MonaResults[2,55] = RightFuncB2[0]
MonaResults[3,55] = LeftFuncB2[2]
MonaResults[4,55] = LeftFuncB2[1]
MonaResults[5,55] = LeftFuncB2[0]

MonaResults[0,56] = RightFuncF2[3]
MonaResults[1,56] = RightFuncF2[2]
MonaResults[2,56] = RightFuncF2[1]
MonaResults[3,56] = RightFuncF2[0]
MonaResults[4,56] = RightFuncF2[3]
MonaResults[5,56] = LeftFuncF2[2]
MonaResults[6,56] = LeftFuncF2[1]
MonaResults[7,56] = LeftFuncF2[0]

MonaResults[0,57] = RightFuncB2[3]
MonaResults[1,57] = RightFuncB2[2]
MonaResults[2,57] = RightFuncB2[1]
MonaResults[3,57] = RightFuncB2[0]
MonaResults[4,57] = RightFuncB2[3]
MonaResults[5,57] = LeftFuncB2[2]
MonaResults[6,57] = LeftFuncB2[1]
MonaResults[7,57] = LeftFuncB2[0]




MonaResults[0,58] = PRightFuncF2[2]
MonaResults[1,58] = PRightFuncF2[1]
MonaResults[2,58] = PRightFuncF2[0]
MonaResults[3,58] = PLeftFuncF2[2]
MonaResults[4,58] = PLeftFuncF2[1]
MonaResults[5,58] = PLeftFuncF2[0]

MonaResults[0,59] = PRightFuncB2[2]
MonaResults[1,59] = PRightFuncB2[1]
MonaResults[2,59] = PRightFuncB2[0]
MonaResults[3,59] = PLeftFuncB2[2]
MonaResults[4,59] = PLeftFuncB2[1]
MonaResults[5,59] = PLeftFuncB2[0]

MonaResults[0,60] = PRightFuncF2[2]
MonaResults[1,60] = PRightFuncF2[1]
MonaResults[2,60] = PRightFuncF2[0]
MonaResults[3,60] = PLeftFuncF2[2]
MonaResults[4,60] = PLeftFuncF2[1]
MonaResults[5,60] = PLeftFuncF2[0]

MonaResults[0,61] = PRightFuncB2[2]
MonaResults[1,61] = PRightFuncB2[1]
MonaResults[2,61] = PRightFuncB2[0]
MonaResults[3,61] = PLeftFuncB2[2]
MonaResults[4,61] = PLeftFuncB2[1]
MonaResults[5,61] = PLeftFuncB2[0]

MonaResults[0,62] = PRightFuncF2[3]
MonaResults[1,62] = PRightFuncF2[2]
MonaResults[2,62] = PRightFuncF2[1]
MonaResults[3,62] = PRightFuncF2[0]
MonaResults[4,62] = PRightFuncF2[3]
MonaResults[5,62] = PLeftFuncF2[2]
MonaResults[6,62] = PLeftFuncF2[1]
MonaResults[7,62] = PLeftFuncF2[0]

MonaResults[0,63] = PRightFuncB2[3]
MonaResults[1,63] = PRightFuncB2[2]
MonaResults[2,63] = PRightFuncB2[1]
MonaResults[3,63] = PRightFuncB2[0]
MonaResults[4,63] = PRightFuncB2[3]
MonaResults[5,63] = PLeftFuncB2[2]
MonaResults[6,63] = PLeftFuncB2[1]
MonaResults[7,63] = PLeftFuncB2[0]

print "Right motor function forwards 1 degree polynomial / linear (Ticks, Time) = "
print RightFuncF1, PRightFuncF1
print "Left motor function forwards 1 degree polynomial / linear linear (Ticks, Time) = "
print LeftFuncF1, PLeftFuncF1
print "Right motor function backwards 1 degree polynomial / linear linear (Ticks, Time) = "
print RightFuncB1, PRightFuncB1
print "Left motor function backwards 1 degree polynomial / linear linear (Ticks, Time) = "
print LeftFuncB1, PLeftFuncB1

print "Right motor function forwards 2 degree polynomial linear (Ticks, Time) = "
print RightFuncF2, PRightFuncF2
print "Left motor function forwards 2 degree polynomial linear (Ticks, Time) = "
print LeftFuncF2, PLeftFuncF2
print "Right motor function backwards 2 degree polynomial  linear (Ticks, Time) = "
print RightFuncB2, PRightFuncB2
print "Left motor function backwards 2 degree polynomial linear (Ticks, Time) = "
print LeftFuncB2, PLeftFuncB2

print "Right motor function forwards 3 degree polynomial linear (Ticks, Time) = "
print RightFuncF3, PRightFuncF3
print "Left motor function forwards 3 degree polynomial linear (Ticks, Time) = "
print LeftFuncF3, PLeftFuncF3
print "Right motor function backwards 3 degree polynomial linear (Ticks, Time) = "
print RightFuncB3, PRightFuncB3
print "Left motor function backwards 3 degree polynomial linear (Ticks, Time) = "
print LeftFuncB3, PLeftFuncB3

np.savetxt("MonaCharacterisationResults.csv", MonaResults, delimiter=",")

plt.show()


