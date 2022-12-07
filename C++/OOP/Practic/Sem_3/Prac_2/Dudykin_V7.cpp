using namespace std;

#include <iostream>
#include <map>
#include <vector>
#include <set>

template <class K, class V>
typename map<K, V>::iterator FindByKey(map<K, V> &m, K key)
{
    return m.find(key);
}

template <class K, class V>
typename map<K, V>::iterator FindByValue(map<K, V> &m, V value)
{
    typename map<K, V>::iterator p = m.begin();
    while (p != m.end())
    {
        if (p->second == value)
            break;
        ++p;
    }
    return p;
}

template <class K, class V>
void print(map<K, V> &m)
{
    typename map<K, V>::iterator p = m.begin();
    while (p != m.end())
    {
        cout << "key: " << p->first << ", value: " << p->second << "\n";
        ++p;
    }
}

template <class K, class V>
map<K, V> filter(map<K, V> &m, V threshold)
{
    map<K, V> result;
    typename map<K, V>::iterator p = m.begin();
    while (p != m.end())
    {
        if (p->second > threshold)
        {
            result.insert({p->first, p->second});
        }
        ++p;
    }
    return result;
}

template <class K, class V>
pair<typename map<K, V>::iterator, bool> insert(map<K, V> &m, pair<K, V> element)
{
    if (m.find(element.first) != m.end())
    {
        throw invalid_argument("Key is already exists!");
    }
    return m.insert(element);
}

template <class K, class V>
vector<V> UniqueTreeValues(map<K, V> &m)
{
    vector<V> result;
    set<V> pom;
    typename map<K, V>::iterator p = m.begin();
    while (p != m.end())
    {
        if (pom.insert(p->second).second == true)
        {
            result.push_back(p->second);
        }
        ++p;
    }

    return result;
}

template <class K, class V>
vector<V> FindByKey(multimap<K, V> &m, K key)
{
    vector<V> result;
    typename multimap<K, V>::iterator p = m.begin();

    while (p != m.end())
    {
        if (p->first == key)
        {
            result.push_back(p->second);
        }
        p++;
    }

    return result;
}

template <class K, class V>
typename multimap<K, V>::iterator FindByValue(multimap<K, V> &m, V value)
{
    typename multimap<K, V>::iterator p = m.begin();
    while (p != m.end())
    {
        if (p->second == value)
            break;
        ++p;
    }
    return p;
}

template <class K, class V>
void print(multimap<K, V> &m)
{
    typename multimap<K, V>::iterator p = m.begin();
    while (p != m.end())
    {
        cout << "key: " << p->first << ", value: " << p->second << "\n";
        ++p;
    }
}

template <class K, class V>
multimap<K, V> filter(multimap<K, V> &m, V threshold)
{
    multimap<K, V> result;
    typename multimap<K, V>::iterator p = m.begin();
    while (p != m.end())
    {
        if (p->second > threshold)
        {
            result.insert({p->first, p->second});
        }
        ++p;
    }
    return result;
}

template <class K, class V>
typename multimap<K, V>::iterator insert(multimap<K, V> &m, pair<K, V> element)
{
    return m.insert({element.first, element.second});
}

template <class K, class V>
vector<V> UniqueTreeValues(multimap<K, V> &m)
{
    vector<V> result;
    set<V> pom;
    typename multimap<K, V>::iterator p = m.begin();
    while (p != m.end())
    {
        if (pom.insert(p->second).second == true)
        {
            result.push_back(p->second);
        }
        ++p;
    }

    return result;
}

template <class K, class V>
multimap<K, V> GetElementsByKey(multimap<K, V> &m, K key)
{
    multimap<K, V> result;
    typename multimap<K, V>::iterator p = m.find(key);
    while (p != m.end() && p->first == key)
    {
        result.insert({p->first, p->second});
        ++p;
    }
    return result;
}

void fillMap(map<string, int> &m)
{
    insert(m, {"one", 1});
    insert(m, {"two", 2});
    insert(m, {"three", 3});
    insert(m, {"four", 4});
    insert(m, {"five", 5});
}

void fillMultiMap(multimap<string, int> &m)
{
    insert(m, {"one", 1});
    insert(m, {"one", 1});
    insert(m, {"one", 1});
    insert(m, {"two", 2});
    insert(m, {"three", 3});
    insert(m, {"four", 4});
    insert(m, {"five", 5});
    insert(m, {"one", 1});
}

int main()
{

    map<string, int> books;
    fillMap(books);

    cout << FindByKey<string, int>(books, "one")->second << "\n";
    cout << FindByValue<string, int>(books, 2)->first << "\n";

    cout << "\n";

    print(books);

    cout << "\n";

    map<string, int> fil_books(filter(books, 2));
    print(fil_books);

    cout << "\n";

    try
    {
        insert(books, {"six", 6});
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    cout << "\n";

    vector<int> unic_val(UniqueTreeValues(books));
    for (auto v : unic_val)
    {
        cout << v << " ";
    }
    cout << "\n\n";

    multimap<string, int> m_books;
    fillMultiMap(m_books);


    vector<int> byKey(FindByKey<string, int>(m_books, "iphone"));
    for (auto v : byKey)
    {
        cout << v << " ";
    }

    cout << "\n" << FindByValue<string, int>(m_books, 2)->first << "\n";


    print(m_books);

    cout << "\n";

    multimap<string, int> fil_m_books(filter(m_books, 2));
    print(fil_m_books);

    cout << "\n";

    unic_val = UniqueTreeValues(m_books);
    for (auto v : unic_val)
        cout << v << " ";
    cout << "\n";

    cout << "\n";

    multimap<string, int> sim_elems(GetElementsByKey<string, int>(m_books, "iphone"));
    print(sim_elems);
}