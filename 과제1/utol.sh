echo "Working Directory:"
read dirname

if [ -n "$dirname" ]
then
	cd $dirname
	if [ $? -ne 0 ]
	then
		echo "Error: Fail to access directory"
		exit 0
	fi
fi

for dir in *
do
	newname=`echo $dir | tr "[a-z] [A-Z]" "[A-Z] [a-z]"`
	mv $dir $newname
done
