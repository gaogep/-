int FindElement(HashTable H, int Key)
{
	int CurPos, NewPos;
	int Ctimes;

	NewPos = CurPos = Hash(Key, H->TableSize);

	while (H->Table[NewPos].Info && H->Table[NewPos].Value != Key) {
		if (++Ctimes%2) {
			NewPos = CurPos + (Ctimes + 1) * (Ctimes + 1) / 4;         // 奇数次冲突
			if (NewPos > H->TableSize) NewPos = NewPos % H->TableSize; // 调整为合法地址
		} else {
			NewPos = CurPos - Ctimes * Ctimes / 4;                     // 偶数次冲突
			while (NewPos < 0) NewPos += H->TableSize;				   // 调整为合法地址
		}
	}

	return NewPos;
}


bool Insert(HashTable H, int Key)
{
	int Pos = FindElement(H, Key);    // 首先验证Key是否已经存在

	if (H->Table[Pos].Info != Legitimate) {
		H->Table[Pos].Info = Legitimate;
		H->Table[Pos].Value = Key;
		return true;
	} else {
		printf("此键值已存在");
		return false;
	}
}