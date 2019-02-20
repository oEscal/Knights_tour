import pygame

############################ Constants ############################
FILE_NAME = "10x10_last.txt"
IMAGE_NAME = "10x10_last_3"
BOARD_NUM = 20

PRINT_NUMBERS = True
SIZE_X = 10
SIZE_Y = 10
SQUARE_SIZE = 100
SQUARE_COLOR = [(0, 0, 0), (255, 255, 255)]
LINE_COLOR = (255, 0, 0)
LINE_WIDTH = 3
CIRCLE_WIDTH = 5

HORSE_STEPS = []
HORSE_POSITIONS_SCREEN = [None]*(SIZE_X*SIZE_Y)


############################ Read data file ############################
file = open(FILE_NAME, "r")
lines = file.readlines()
for i in range(SIZE_X):
   line = lines[BOARD_NUM*(SIZE_X + 1) + i].split('\t')
   del line[len(line) - 1]
   HORSE_STEPS.append(list(map(int, line)))
file.close()

for n1 in range(SIZE_X):
   for n2 in range(SIZE_Y):
      HORSE_POSITIONS_SCREEN[HORSE_STEPS[n1][n2] - 1] = (n1*SQUARE_SIZE + SQUARE_SIZE//2, n2*SQUARE_SIZE + SQUARE_SIZE//2)


############################ Draw the requested board ############################
pygame.init()
font = pygame.font.SysFont("couriernew", 72)
clock = pygame.time.Clock()
screen = pygame.display.set_mode((SQUARE_SIZE*SIZE_X, SQUARE_SIZE*SIZE_Y))

running = True
while running:
   for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            running = False

   for n1 in range(SIZE_X):
      for n2 in range(SIZE_Y):
         square_color = SQUARE_COLOR[(n1 + n2)%len(SQUARE_COLOR)]
         pygame.draw.rect(screen, square_color, pygame.Rect(n1*SQUARE_SIZE, n2*SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE))
         
         if PRINT_NUMBERS and HORSE_STEPS[n1][n2] != 0:
            font_color = SQUARE_COLOR[(n1 + n2 + 1)%len(SQUARE_COLOR)]
            text = font.render(str(HORSE_STEPS[n1][n2]), True, font_color)
            screen.blit(text, (n1*SQUARE_SIZE, n2*SQUARE_SIZE))

   for i in range(len(HORSE_POSITIONS_SCREEN) - 1):
      if HORSE_POSITIONS_SCREEN[i + 1] == None:
         break;
      pygame.draw.line(screen, LINE_COLOR, HORSE_POSITIONS_SCREEN[i], HORSE_POSITIONS_SCREEN[i + 1], LINE_WIDTH)
      pygame.draw.circle(screen, LINE_COLOR, HORSE_POSITIONS_SCREEN[i], CIRCLE_WIDTH, CIRCLE_WIDTH)
      pygame.draw.circle(screen, LINE_COLOR, HORSE_POSITIONS_SCREEN[i + 1], CIRCLE_WIDTH, CIRCLE_WIDTH)

   pygame.display.flip()

   #save the chess board in an jpeg image and exit the program
   pygame.image.save(screen, IMAGE_NAME + ".jpeg")
   exit()