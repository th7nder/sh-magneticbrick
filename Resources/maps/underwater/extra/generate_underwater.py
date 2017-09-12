import os 
import random

class Extra:
	name = ""
	posX = 0
	posY = 0
	width = 0
	height = 0
	orientation = ""
	def __init__(self, name, posX, posY, width, height, orientation):
		self.name = name
		self.posX = posX
		self.posY = posY
		self.width = width
		self.height = height
		self.orientation = orientation


names = ['UEFishOrange', 'UEFishGreen', 'UEFishRed', 'UETentacle']
sizesX = [215, 215, 215, 491]
sizesY = [69, 69, 69, 287]
endY = 22000


for level in range(1, 7):
	extras = []
	lastRightY = 0
	lastLeftY = 0
	randomRightDist = 0
	randomLeftDist = 0
	distRangeStart = 0.75 * 1920
	distRangeEnd = 1.25 * 1920


	lastLeftY = 0
	lastRightY = 0
	distRangeStart = 0.4 * 1920
	distRangeEnd = 1.1 * 1920
	while lastLeftY < endY:
		leftId = random.randint(0, len(names) - 1)
		name = names[leftId]
		y = lastLeftY + random.randint(distRangeStart, distRangeEnd)
		extra = Extra(name, 0, y, sizesX[leftId], sizesY[leftId], "left")
		lastLeftY = y + sizesY[leftId]

		extras.append(extra)


	while lastRightY < endY:
		id = random.randint(0, len(names) - 1)
		##while id == leftId:
		##	id = random.randint(0, len(names) - 1)

		name = names[id]
		y = lastRightY + random.randint(distRangeStart, distRangeEnd)
		extra = Extra(name, 1080 - sizesX[id], y, sizesX[id], sizesY[id], "right")
		lastRightY = y + sizesY[id]

		extras.append(extra)



	with open("underwater_0" + str(level) + ".extras", "w") as f:
		for extra in extras:
			f.write(extra.name + ";" + extra.orientation + ";" + str(extra.width) + ";" + str(extra.height) + ";" + str(extra.posX) + ";" + str(extra.posY) + "\n")

		f.close()
