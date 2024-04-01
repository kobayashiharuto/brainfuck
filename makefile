# コンパイラ設定
CC = gcc
CFLAGS = -O1
BFC = ./main

# 出力ディレクトリ
OUTDIR = ./output

# 引数から受け取ったBrainfuckファイル
BF_FILE ?= ./target/m.bf

# ターゲット設定
ASM_FILE = $(OUTDIR)/m.s
OBJ_FILE = $(OUTDIR)/m.o
EXEC_FILE = $(OUTDIR)/m

# main.cをコンパイル
all: $(BFC)

$(BFC): main.c
	$(CC) $(CFLAGS) -o $(BFC) main.c

# Brainfuckファイルからアセンブリファイルを生成
asm: $(ASM_FILE)

$(ASM_FILE): $(BFC) $(BF_FILE)
	mkdir -p $(OUTDIR)
	$(BFC) < $(BF_FILE) > $(ASM_FILE)

# アセンブリファイルをコンパイルして実行ファイルを生成
build: $(EXEC_FILE)

$(EXEC_FILE): $(ASM_FILE)
	nasm -f elf64 $(ASM_FILE) -o $(OBJ_FILE)
	ld -o $(EXEC_FILE) $(OBJ_FILE)

# 生成した実行ファイルを実行
run: $(EXEC_FILE)
	$(EXEC_FILE)

# クリーンアップ
clean:
	rm -f $(BFC) $(ASM_FILE) $(OBJ_FILE) $(EXEC_FILE)
