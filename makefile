# コンパイラ設定
CC = gcc
CFLAGS = -Ofast -march=native -flto
BFC = ./main

# 出力ディレクトリ
OUTDIR = ./output

# 引数から受け取ったBrainfuckファイル
BF_FILE ?= ./target/m.bf

# アセンブリファイル名
ASM_FILE = $(OUTDIR)/m.s

# オブジェクトファイル名
OBJ_FILE = $(ASM_FILE:.s=.o)

# 実行ファイル名
EXEC_FILE = $(OUTDIR)/m

.PHONY: asm build run clean

# Brainfuckファイルからアセンブリファイルを生成
asm:
	$(BFC) < $(BF_FILE) > $(ASM_FILE)

# アセンブリファイルをコンパイルして実行ファイルを生成
build: asm
	nasm -f elf64 $(ASM_FILE) -o $(OBJ_FILE)
	ld -o $(EXEC_FILE) $(OBJ_FILE)

# 実行ファイルを実行
run: build
	$(EXEC_FILE)

# 出力ファイルをクリーンアップ
clean:
	rm -f $(ASM_FILE) $(OBJ_FILE) $(EXEC_FILE)
