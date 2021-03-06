#include <malloc.h>
#include <foundation\PxAllocatorCallback.h>

namespace physx {

	class PxDefaultAllocator : public PxAllocatorCallback
	{
		void* allocate(size_t size, const char*, const char*, int)
		{
			return _aligned_malloc(size, 16);
		}

		void deallocate(void* ptr)
		{
			_aligned_free(ptr);
		}
	};

}