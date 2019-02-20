SIZE_X = 5
SIZE_Y = 5
NUMBER_BOARDS = 28

files = [open("5x5_last_top_left.txt", "r"),
         open("5x5_last_bottom_left.txt", "r"),
         open("5x5_last_top_right.txt", "r"),
         open("5x5_last_bottom_right.txt", "r")]
file_write = open("10x10_last.txt", "w")

lines = []
for i in range(len(files)):
   lines.append(files[i].readlines())

all_boards = []
for board_num in range(NUMBER_BOARDS):
   all_boards.append([]);
   for n in range(2):
      for i in range(SIZE_X):
         line = lines[(n%2)*2][board_num*(SIZE_X + 1) + i].split('\t')
         del line[len(line) - 1]

         line += lines[(n%2)*2 + 1][board_num*(SIZE_X + 1) + i].split('\t')
         del line[len(line) - 1]

         all_boards[board_num].append(list(map(int, line)))

for i in range(len(files)):
   files[i].close()

for i in all_boards:
   file_write.write(str(i).replace(", ", "\t")
                          .replace("]\t[", "\t\n")
                           .replace("[[", "")
                           .replace("]]", "\t"))
   file_write.write("\n\n")
file_write.close()