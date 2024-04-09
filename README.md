# Brainfuckコンパイラ

bf を C言語に変換して gcc でコンパイルするやつ

## 動かし方

以下で実行可能。

```
make run 
```

bfからCに変換するやつをコンパイルして、それ使ってbfをCに変換して、Cをgccでコンパイルして、実行するまでやってくれる。

コンパイルオプションとかはmakefileでいじれる。


## 手法について

### 基本アプローチ

以下の2つのプロセスにおいて効率化を図る

- bfをCに変換する部分
- 変換されたCをgccでコンパイルする部分

## ログ

- 変換する部分はそのまま対応するものに変換し、gccのオプションを `-Ofast -march=native -flto` にして高速化を図る。
  - 約0.58秒
- `>`, `<`, `+`, `-` をひとつひとつ出力するのではなく、まとめて加算,減算するようにする
  - 約0.56秒
- `[-]`を`*ptr = 0`に変換する
  - `[-]`は、そのポインタが指すメモリを0なるまで1ずつ減らしていくループ処理を指すため、ループさせずに直接0にしてしまえばよい。
  - 約0.52秒

## 他の自分のbrainfuck関連のリポジトリ

- [brainfuck_interpreter_js_vs_wasm](https://github.com/kobayashiharuto/brainfuck_interpreter_js_vs_wasm): ブラウザで Brainfuck のインタプリタを JS と WASM で比較して遊べるやつ
- [brainfuck/asm](https://github.com/kobayashiharuto/brainfuck/tree/asm): アセンブリに直接変換するのを試みたブランチ(大して知識がないので意味があまりなかった...)

## 関連リポジトリ

- [seelx3/bf-cpp](https://github.com/seelx3/bf-cpp)
- [tuesdayjz/bf-interpreter](https://github.com/tuesdayjz/bf-interpreter)
- [uchijo/bf-eval](https://github.com/uchijo/bf-eval)
- [QRWells/bf-jit](https://github.com/QRWells/bf-jit)
- [mkihr-ojisan/bf](https://github.com/mkihr-ojisan/bf)
- [n0-t0/brainfuck](https://github.com/n0-t0/brainfuck)
- [hydrokhoos/brainfuck_python](https://github.com/hydrokhoos/brainfuck_python)
