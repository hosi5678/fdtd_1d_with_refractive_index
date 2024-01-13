import os
import imageio

# 入力と出力のパスを指定
input_folder = 'pings'
output_file = 'output.mp4'

# 連番のPNG画像を取得
image_files = [f for f in os.listdir(input_folder) if f.endswith('.png')]
image_files.sort()

# 画像から動画を作成
with imageio.get_writer(output_file, duration=0.1) as writer:
    for image_file in image_files:
        image_path = os.path.join(input_folder, image_file)
        img = imageio.imread(image_path)
        writer.append_data(img)

print(f'MP4動画が作成されました: {output_file}')
