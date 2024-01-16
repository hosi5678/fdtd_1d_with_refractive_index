import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

header_dir="./graph/"
file_name="graph.png"

data_limitation=500

# 第一引数(CSVファイルのパス)を文字列に変換する。
file_path=str(sys.argv[1])

# file pathからファイル名だけを取り出す

# ファイル名（拡張子あり）
file_name_with_extension = os.path.basename(file_path)

# 拡張子を除いたファイル名
file_name_without_extension, extension = os.path.splitext(file_name_with_extension)

# CSVファイルをPandasのSeriesに読み込む　
df = pd.read_csv(file_path,header=None,names=["x","data"] )

if len(df)>=data_limitation :
   df=df.head(data_limitation);

# file名の表示
print(file_path+" has readed.")


# 折れ線グラフを作成して表示
plt.plot(df["x"] , df["data"], linestyle="solid")

# グラフにタイトルや軸ラベルを追加（必要に応じて）
plt.title('title-none')

# x軸ラベルの設定
plt.xlabel('x-axis')

# y軸ラベルの設定
plt.ylabel('y-axis')

# plt.show()に後にsaveすると消えてしまう。
plt.savefig(header_dir+file_name_without_extension+".png")

print(str(header_dir)+str(file_name_without_extension)+".png was saved..")

# グラフを表示
plt.show()

# メモリの解放
plt.clf()
plt.close()
