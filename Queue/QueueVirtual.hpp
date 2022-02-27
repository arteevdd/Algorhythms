#ifndef QUEUE_VIRTUAL_HPP
#define QUEUE_VIRTUAL_HPP

template <class T>
class QueueVirtual
{
public:
	virtual ~QueueVirtual() = default;

	virtual void enQueue(const T& e) = 0;  
	virtual T deQueue() = 0;  
	virtual bool isEmpty() const = 0;
};

#endif
