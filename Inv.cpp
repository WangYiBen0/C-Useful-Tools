#include <vector>
#include <utility>
typedef long long LL;
std::pair<LL, LL> exgcd_answer;
LL exgcd(const LL &a, const LL &b, LL &x = exgcd_answer.first, LL &y = exgcd_answer.second) // 扩展欧几里得算法
{
	if (b == 0)
	{
		x = 1, y = 0;
		return a;
	}
	LL ret = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return ret;
}
LL power(LL a, LL n, const LL &mod = LONG_LONG_MAX)
{
	LL res = 1;
	while (n)
	{
		if (n & 1)
			res = res * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return res;
}
enum _INV_METHOD_ENUMERATION_
{
	Auto,
	Exgcd,
	Fetmat
};
LL inv(LL a, const LL &mod, const _INV_METHOD_ENUMERATION_ &method = Auto) // 求a在mod下的逆元，不存在逆元返回-1
{
	a %= mod;
	const static auto ExGCD = [](const LL &a, const LL &mod) -> LL
	{
		LL x, y;
		LL d = exgcd(a, mod, x, y);
		return d == 1 ? (x % mod + mod) % mod : -1;
	};
	const static auto QuickPower = [](const LL &a, const LL &mod) -> LL
	{
		return power(a, mod - 2, mod);
	};
	const static auto isprime = [](const LL &n) -> bool
	{
		if (n == 1)
			return false;
		if (n == 2)
			return true;
		if (n & 1 == 0)
			return false;
		for (int i = 3; i * i <= n; i += 2)
			if (n % i == 0)
				return false;
		return true;
	};
	switch (method)
	{
	case Auto:
		if (isprime(mod))
			return ExGCD(a, mod);
		else
			return QuickPower(a, mod);
	case Exgcd:
		return ExGCD(a, mod);
	case Fetmat:
		return QuickPower(a, mod);
	}
	return -1;
}
std::vector<LL> getInv(LL mod)
{
	std::vector<LL> res(mod + 1, 0);
	res[1] = 1;
	for (int i = 2; i < mod; i++)
		res[i] = (mod - mod / i) * res[mod % i] % mod;
	return res;
}