#pragma once

#include <Poco/AbstractCache.h>
#include "IlluminatePoolStrategy.h"

using Poco::AbstractCache;
using Poco::FastMutex;
using Poco::Timestamp;

template <
	class TKey,
	class TValue,
	class TMutex = FastMutex,
	class TEventMutex = FastMutex
>
class IlluminatePool : public AbstractCache<TKey, TValue, IlluminatePoolStrategy<TKey, TValue>, TMutex, TEventMutex>
{
public:
	IlluminatePool(Timestamp::TimeDiff expire = 600000) :
		AbstractCache<TKey, TValue, IlluminatePoolStrategy<TKey, TValue>, TMutex, TEventMutex>(IlluminatePoolStrategy<TKey, TValue>(expire))
	{
	}

	~IlluminatePool()
	{
	}

private:
	IlluminatePool(const IlluminatePool& aCache);
	IlluminatePool& operator = (const IlluminatePool& aCache);
};