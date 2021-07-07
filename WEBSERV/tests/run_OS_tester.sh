mkdir -p logs
cd logs
rm -f ./*
cd ../
rm -f html_pages/Downloads/Download_* html_pages/Downloads/file_should_exist_after html_pages/Downloads/multiple_same


mkdir -p YoupiBanane
touch YoupiBanane/youpi.bad_extension
touch YoupiBanane/youpi.bla
mkdir -p YoupiBanane/nop
touch YoupiBanane/nop/youpi.bad_extension
touch YoupiBanane/nop/other.pouic
mkdir -p YoupiBanane/Yeah
touch YoupiBanane/Yeah/not_happy.bad_extension

bash ./runtest.sh