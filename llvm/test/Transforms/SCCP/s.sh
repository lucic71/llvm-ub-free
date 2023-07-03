for f in 2004-12-10-UndefBranchBug.ll 2008-01-27-UndefCorrelate.ll PR26044.ll indirectbr.ll ipsccp-branch-unresolved-undef.ll ipsccp-phi-one-pred-dead.ll return-zapped.ll switch-constantfold-crash.ll switch-undef-constantfoldterminator.ll
do
	cp $f trap-$f
done
