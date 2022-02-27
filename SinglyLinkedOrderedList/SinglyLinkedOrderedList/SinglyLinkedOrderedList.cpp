#include "SinglyLinkedOrderedList.h"

SinglyLinkedOrderedList::SinglyLinkedOrderedList(const SinglyLinkedOrderedList& list)
{
    SinglyLinkedOrderedList::Node* p = list.head_;
    while (p != nullptr)
    {
        add(p->item_);
        p = p->next_;
    }
}

SinglyLinkedOrderedList::~SinglyLinkedOrderedList()
{
    clear();
}

bool SinglyLinkedOrderedList::add(int item)
{
    Node* p = new Node(item);

    if (head_ == nullptr)
        head_ = p;
    else
    {
       
        if (item < head_->item_)
        {
            p->next_ = head_;
            head_ = p;
        }
        else
        {
            Node* t = head_;
            while (t->next_ != nullptr && t->next_->item_ < item)
            {
                t = t->next_;
            }
            if (t->next_ != nullptr && t->next_->item_ == item || t->item_ == item)
            {
                delete p;
                return false;
            }

            p->next_ = t->next_;
            t->next_ = p;
        }
    }

    return true;
}

bool SinglyLinkedOrderedList::find(int item) const
{
    Node* p = head_;

    while (p != nullptr && p->item_ < item)
        p = p->next_;

    if (p != nullptr && p->item_ == item)
        return true;
    return false;
}

bool SinglyLinkedOrderedList::remove(int item)
{
    if (is_empty())
        return false;

    Node* p = head_;

    if (p->item_ == item) {
        head_ = head_->next_;
        delete p;
    }
    else
    {
        while (p->next_ != nullptr && p->next_->item_ < item)
            p = p->next_;

        if (p->next_ == nullptr || p->next_->item_ != item)
            return false;

        Node* temp = p->next_;
        p->next_ = temp->next_;
        delete temp;
    }

    return true;
}

bool SinglyLinkedOrderedList::is_empty() const
{
    return head_ == nullptr;
}

void SinglyLinkedOrderedList::clear()
{
    SinglyLinkedOrderedList::Node* p = head_;
    SinglyLinkedOrderedList::Node* t;
    while (p != nullptr)
    {
        t = p->next_;
        delete p;
        p = t;
    }
    head_ = nullptr;
}

void SinglyLinkedOrderedList::union_list(SinglyLinkedOrderedList& list)
{
    SinglyLinkedOrderedList::Node* p = list.head_;
    while (p != nullptr)
    {
        if (!find(p->item_)) {
            add(p->item_);
        }
        p = p->next_;
    }

    list.clear();
}

void SinglyLinkedOrderedList::difference(const SinglyLinkedOrderedList& list)
{
    SinglyLinkedOrderedList::Node* p = head_;
    while (p != nullptr)
    {
        if (list.find(p->item_)) {
            SinglyLinkedOrderedList::Node* t = p->next_;
            remove(p->item_);
            p = t;
        }
        else
            p = p->next_;
    }
}

SinglyLinkedOrderedList SinglyLinkedOrderedList::intersect(const SinglyLinkedOrderedList& list)
{
    SinglyLinkedOrderedList res;
    SinglyLinkedOrderedList::Node* p = head_;
    while (p != nullptr)
    {
        if (list.find(p->item_)) {
            res.add(p->item_);
        }
        p = p->next_;
    }

    return res;
}

std::ostream& operator<<(std::ostream& out, const SinglyLinkedOrderedList& list)
{
    SinglyLinkedOrderedList::Node* p = list.head_;
    while (p != nullptr)
    {
        out << p->item_ << " ";
        p = p->next_;
    }
    out << std::endl;
    return out;
}