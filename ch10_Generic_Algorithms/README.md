## 10.1
```cpp
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> v1 = {1,2,3,1,1};

	cout << count(v1.cbegin(), v1.cend(), 1) << endl;

	return 0;
}
```

## 10.2
```cpp
#include <list>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
	list<string> l1 = {"a", "b", "c", "a", "aa"};

	cout << count(l1.cbegin(), l1.cend(), "a") << endl;

	return 0;
}
```

## 10.3
```cpp
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> v1 = {1,2,3,1,1};

	cout << accumulate(v1.cbegin(), v1.cend(), 0) << endl;

	return 0;
}
```

## 10.4
结果默认是int类型的，精度会降低。
```cpp
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	vector<double> v1 = {1,2,3.1,1,1};

	cout << accumulate(v1.cbegin(), v1.cend(), 0) << endl;

	return 0;
}
```

## 10.5
equal会比较指针地址，而不是字符串值，比较的结果与string类型的不一致。

## 10.6
