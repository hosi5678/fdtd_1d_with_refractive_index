# libraryの読み込み
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import sys

import matplotlib.ticker as ticker

file_path=str(sys.argv[1])

df=pd.read_csv(file_path)

fig=plt.figure(figsize=(1080/80,1080/80),dpi=80)

fig.suptitle('Heatmap',fontsize=20)

sns.heatmap(df,cmap='coolwarm',cbar=True,center=0.0)

plt.savefig("./graph/heatmap.png")

plt.show();

# メモリの解放
plt.clf()
plt.close()
