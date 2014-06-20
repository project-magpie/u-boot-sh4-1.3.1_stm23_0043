
release_dir=release

if [ -d $release_dir ]; then
	rm $release_dir -rf
fi

mkdir $release_dir

cp u-boot $release_dir
cp u-boot.bak.bin $release_dir
cp u-boot.bin $release_dir

touch $release_dir/spark7111

describe=`git describe --dirty --always --tags`
touch $release_dir/$describe

git log --graph --decorate --oneline > $release_dir/history.txt
