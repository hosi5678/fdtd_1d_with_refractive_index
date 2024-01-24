import os
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

from count_csv_files import count_csv_files
from shell_command import shell_command

head_path="./"

# csv filesのフォルダパス
csv_dir="./ey_timestep_csvs/"

# outputするフォルダパス
png_dir="./pngs/"

output_dir="./mp4/"
output_file="./mp4/output.mp4"

reflactive_range_file="./csv_files/ref_range.csv"
df=pd.read_csv(reflactive_range_file,header=None)

n_start=df.iloc[0,1]
n_end=df.iloc[1,1]+1

print("n start= "+str(n_start))
print("n end= "+str(n_end))

# csvのファイル数の取得
timestep = count_csv_files(csv_dir)

# print(str(timestep)+" csv files were found.")

ey_range_file="./csv_files/ey_range.csv"

df=pd.read_csv(ey_range_file,header=None)

print("ey_max="+str(df.iloc[0].max()))
print("ey_min="+str(df.iloc[1].min()))

# 最大値、最小値の取得
max=df.iloc[0].max()
min=df.iloc[1].min()


n_value_file="./csv_files/ref_value.csv"
df_n_value=pd.read_csv(n_value_file,header=None)
# 2列目を読み出す
n_value=df_n_value.iloc[:,1]

# print(n_value)

timestep = int(input("input timestep number.(>0)"))

for i in range(timestep):
    
    # 6桁固定のiを作り出す
    fmt_i = '{:06d}'.format(i)
    csv_file=csv_dir+"ey_timestep_"+fmt_i+".csv"
    
    # data frameに読み込む
    df=pd.read_csv(csv_file,header=None)
    
    # x軸のデータ（1行目）
    xticks = df.iloc[0]

    # データ部分（2行目以降）
    data = df.iloc[1:]

    # DataFrameを転置する（行と列を入れ替える）
    # 折れ線グラフは縦方向に転置し、heatmapは横方向に読み込む

    # figure(全体図)のサイズをfull hdに設定
    fig=plt.figure(figsize=(1920/80,1080/80),dpi=80)

    # 2行1列の1行目
    ax1=fig.add_subplot(2,1,1)
    
    ax1.set_title('Ey Amplitude',{"fontsize":20})
    
    ax1.set_xlabel('x position',{"fontsize":15})
    ax1.set_ylabel('Ey amplitude')
 
    ax1.set_xlim(left=0)
    ax1.set_xlim(right=len(xticks))

    ax1.set_xticks( np.arange(0, len(xticks), 5) )
    # ax1.set_yticks( np.arange(min , max , 0.0000025) )

    ax1.plot(df.T)

    ax1.set_ylim(top=max)
    ax1.set_ylim(bottom=min)
    
    # 折れ線グラフのプロット
    ax1.plot(df.T,color="gray")
        
    ax2=ax1.twinx()

    ax2.plot(n_value)
    
    ax2.set_ylabel("reflactive index")

    # 2行1列の2行目
    ax2=fig.add_subplot(2,1,2)

    ax2.set_title('Heatmap of Ey',{"fontsize": 20})
    
    # heatmapにもx軸を設定する。間隔はxticklabels=5で設定する。
    heatmap=sns.heatmap(data, xticklabels=5, yticklabels=False,cmap='coolwarm',cbar=False,center=0.0)
    # ax2.xaxis.set_major_locator(ticker.MultipleLocator(5)) 
    heatmap.set_xlabel('x position' , {"fontsize":15})
    
    line_position=n_start
    
    plt.axvline(x=line_position,color="black",linestyle="-",linewidth=2)
    
    line_position=n_end
    plt.axvline(x=line_position,color="black",linestyle="-",linewidth=2)

    
    plt.suptitle("timestep="+str(i),fontsize=25)
    # plt.tight_layout()

    # ファイルを保存
    plt.savefig(png_dir+"png_"+fmt_i+".png")
    
    # saveの表示
    print(png_dir+"png_"+fmt_i+".png"+"/"+str(timestep)+" was created.")
    
    # csv fileの削除
    os.unlink(csv_file)
    
    # メモリの解放
    plt.clf()
    plt.close()

# 最後は下記のコマンドで動画ができる。
# ffmpeg -r 10 -i ../pngs/png_%06d.png -c:v libx264 -pix_fmt yuv420p output.mp4


# 後処理
command="rm ./mp4/output.mp4"
shell_command(command)

command="ffmpeg -r 10 -i ./pngs/png_%06d.png -c:v libx264 -pix_fmt yuv420p ./mp4/output.mp4"
shell_command(command)    
    
command="rm -rf ./pngs/*.png"
shell_command(command)

command="vlc ./mp4/output.mp4"
shell_command(command)

command="rm -rf ./ey_timestep_csvs/*.csv"
shell_command(command)
