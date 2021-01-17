CC = gcc
# -D是添加宏
CFLAGS = -g -DDEBUG -lm -Wall -I include -W -Wstrict-prototypes -Wmissing-prototypes -Wsystem-headers -fgnu89-inline
#CFLAGS = -g -lm -Wall -I . -W -Wstrict-prototypes -Wmissing-prototypes -Wsystem-headers -fgnu89-inline
TARGET = spr
DIRS =  ./src
CFILES = $(foreach dir, $(DIRS),$(wildcard $(dir)/*.c))
OBJS = $(patsubst %.c,%.o,$(CFILES)) 
$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)
clean:
	-$(RM) $(TARGET) $(OBJS)
r: clean $(TARGET)
