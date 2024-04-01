# コンパイラ設定
CC = gcc
CFLAGS = -Ofast -march=native -flto
BFC = ./main

# 出力ディレクトリ
OUTDIR = ./output

# 引数から受け取ったBrainfuckファイル
BF_FILE ?= ./target/m.bf

C_FILE = $(OUTDIR)/$(notdir $(BF_FILE:.bf=.c))
EXE_FILE = $(OUTDIR)/$(notdir $(BF_FILE:.bf=))

# デフォルトターゲット
all: bf2c $(EXE_FILE)

# Brainfuckコンパイラ（bf_compiler）のビルド
bf2c: main.c
	$(CC) $(CFLAGS) -o main main.c

# BrainfuckファイルからCファイルへの変換
$(C_FILE): $(BF_FILE) bf2c
	mkdir -p $(OUTDIR)
	$(BFC) < $(BF_FILE) > $(C_FILE)

# Cファイルから実行ファイルへのコンパイル
$(EXE_FILE): $(C_FILE)
	$(CC) $(CFLAGS) -o $(EXE_FILE) $(C_FILE)

# 実行
run: $(EXE_FILE)
	$(EXE_FILE)

# クリーンアップ
clean:
	rm -f bf_compiler
	rm -rf $(OUTDIR)
