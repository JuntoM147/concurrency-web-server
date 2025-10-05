CC=clang
CFLAGS=-Wall -Wextra
SERVER_DIR=src/server
HANDLER_DIR=src/server/handle_conn

server: server.o handler.o parser.o send_error.o serve_file.o extract_path.o
	$(CC) $(CFLAGS) server.o handler.o parser.o send_error.o serve_file.o extract_path.o -o server

server.o: $(SERVER_DIR)/server.c
	$(CC) $(CFLAGS) -c $(SERVER_DIR)/server.c -o server.o

handler.o: $(HANDLER_DIR)/handler.c
	$(CC) $(CFLAGS) -c $(SERVER_DIR)/handle_conn/handler.c -o handler.o

parser.o: $(HANDLER_DIR)/parser.c
	$(CC) $(CFLAGS) -c $(HANDLER_DIR)/parser.c -o parser.o

send_error.o: $(HANDLER_DIR)/send_error.c
	$(CC) $(CFLAGS) -c $(HANDLER_DIR)/send_error.c -o send_error.o

serve_file.o: $(HANDLER_DIR)/serve_file.c
	$(CC) $(CFLAGS) -c $(HANDLER_DIR)/serve_file.c -o serve_file.o

extract_path.o: $(HANDLER_DIR)/extract_path.c
	$(CC) $(CFLAGS) -c $(HANDLER_DIR)/extract_path.c -o extract_path.o

clean:
	rm -f *.o server

