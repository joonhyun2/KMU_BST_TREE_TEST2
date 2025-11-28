/*
* File Processing Report 2024 - Balanced Tree skeleton code in C/C++
*
* 본 Skeleton code는 구현에 도움을 주기 위해 작성된 코드입니다.
* ❗️본 Skeleton code는 과제의 요구 조건을 완전히 충족시키지 않을 수 있습니다.❗️
* ❗️최종 점수 산정은 과제 PDF에 명시된 요구 사항을 기준으로 이루어집니다.❗️
*
*/

#include <iostream>
#include <stack>

template <class _Tp, std::size_t M> class Node;
template <class _Tp, std::size_t M> class BT;

/*
* 아래는 반드시 사용해야하는 Node 클래스입니다.
* 멤버 변수는 추가, 삭제 및 변경이 불가능합니다.
*/
template <class _Tp, std::size_t M = 4>
class Node {
	private: // Member types
		typedef _Tp					__key_type;
		typedef Node<__key_type>*	__node_pointer;
		typedef std::size_t			size_type;
	
	public: // Member variables
		__key_type		__keys_[M - 1];
		__node_pointer	__children_[M];
		size_type		__size_;
	
	public: // Constructor //❗❗
		// ✅ 기본 생성자 (필수)
    Node() {
        __size_ = 0;
        for (size_type i = 0; i < M; i++)
            __children_[i] = nullptr;
    }

    // ✅ 키 기반 생성자 (단 하나만 존재해야 함)
    explicit Node(const __key_type& key) {
        __size_ = 0;
        for (size_type i = 0; i < M; i++)
            __children_[i] = nullptr;
        __push_front(key, nullptr);
    }

	public: // Modifier
		void __push_front(const __key_type& __key, const __node_pointer& __np) {
			__children_[__size_ + 1] = __children_[__size_];
			for (size_type __i = __size_; 0 < __i; --__i) {
				__keys_[__i] = __keys_[__i - 1];
				__children_[__i] = __children_[__i - 1];
			}
			__keys_[0] = __key;
			__children_[0] = __np;
			++size();
		}
		void __push_back(const __key_type& __key, const __node_pointer& __np) {
			__keys_[size()] = __key;
			__children_[size() + 1] = __np;
			++size();
		}
		__key_type __pop_front() {//❗❗수정
			const __key_type __ret = __keys_[0];
			
			for (size_type __i = 0; __i < __size_ - 1; ++__i) {
				__keys_[__i] = __keys_[__i + 1];
				this->__children_[__i] = this->__children_[__i + 1];
			}
			this->__children_[__size_ - 1] = this->__children_[__size_];
			--size();

			return __ret;
		}
		__key_type __pop_back() { return __keys_[--size()]; }

	public: // Capacity
		size_type& size() { return __size_; }
		const size_type& size() const { return __size_; }

	/*
	* 아래는 inorder traversal을 대체할 수 있는 operator<< 입니다.
	* 반드시 아래의 함수를 사용해야할 필요는 없습니다.
	*/
	friend std::ostream& operator<<(std::ostream& os, const __node_pointer& __np) {
		if (__np == nullptr || __np->size() == 0) {
			return os;
		}

		os << '<';
		os << __np->__children_[0] << ' ';
		for (std::size_t __i = 0; __i < __np->size() - 1; __i++) {
			os << __np->__keys_[__i] << ' ';
			if (__np->__children_[__i + 1] != nullptr) {
				os << __np->__children_[__i + 1] << ' ';
			}
		}
		os << __np->__keys_[__np->size() - 1] << ' ';
		os << __np->__children_[__np->size()];
		os << '>';

		return os;
	}
};

/*
* 아래 함수들의 설계 방식은 Tree와 Node의 구동부를 구현하기 위해 추천드리는 설계 방식입니다.
* 반드시 아래의 설계 방식을 따라야 하는 것은 아닙니다.
*/

/*
* PDF에 명시되어있는 출력 형식에 유의하세요.
* ❗️잘못된 출력 형식은 0점 처리됩니다.❗️
*/
template <class _NodePtr>
void __inorder(_NodePtr __x) {
	if (__x == nullptr || __x->size() == 0) {
		return ;
	}

	std::cout << '<';
	std::cout << __x->__children_[0] << ' ';
	for (std::size_t __i = 0; __i < __x->size() - 1; __i++) {
		std::cout << __x->__keys_[__i] << ' ';
		if (__x->__children_[__i + 1] != nullptr) {
			std::cout << __x->__children_[__i + 1] << ' ';
		}
	}
	std::cout << __x->__keys_[__x->size() - 1] << ' ';
	std::cout << __x->__children_[__x->size()];
	std::cout << '>';

	return ; // ❗❗수정함
}

// Dangling pointer를 방지하기 위해 __x를 참조 타입으로 받도록 설계하였습니다.
template <class _NodePtr>
void __clear(_NodePtr& __x) {
	if (__x == nullptr) {
		return;
	}
	
	for (std::size_t __i = 0; __i <= __x->size(); __i++) {
		__clear(__x->__children_[__i]);
	}
	delete __x;
	__x = nullptr;
}
template <class _NodePtr, class _Tp, std::size_t M>
std::pair<std::stack<_NodePtr>, bool> searchPath(_NodePtr& __root, const _Tp& __key){
	_NodePtr x = __root;
	std::stack<_NodePtr> path;
	std::size_t i = 0;
	// x = __root 가 nullptr인 경우는 없음
	do{ //❗❗ while - do로 바꿔야할수도 있음
		i=0;
		while( i<=x->__size_-1 && __key>x->__keys_[i])
		{
			i++;
		}
		if( i<= x->__size_-1 && __key==x->__keys_[i]){
			path.push(x);
			return std::pair<std::stack<_NodePtr>, bool>(path,  true);

		}

		path.push(x);

		
		x=x->__children_[i];

	} while(x!=nullptr);

	return std::pair<std::stack<_NodePtr>, bool>(path,  false);
}

template <class _NodePtr, class _Tp, std::size_t M>
void insertKey(_NodePtr& __root, _NodePtr x, _NodePtr y, _Tp __key){
    (void)__root;//❗❗❗
// y : 전 단계에서 분할한 노드 (첫 단계에서는 null)
	int i = x->__size_-1; // key의 인덱스 값: 최대 1
	while(i>=0 && __key<x->__keys_[i]){
		x->__keys_[i+1]=x->__keys_[i];
		x->__children_[i+2]=x->__children_[i+1];
		i--;
	}

	x->__keys_[i+1]=__key;
	x->__children_[i+2]= y;
	x->__size_=x->__size_+1;
}

template <class _NodePtr, class _Tp, std::size_t M>
std::pair<_Tp, _NodePtr> splitNode(_NodePtr& __root, _NodePtr x, _NodePtr y, _Tp __key){
    (void)__root;//❗❗❗
	int size = x->__size_+1; // 새로운 tempNode의 키의 개수 4
	
	_NodePtr tempChildren[5];
	_Tp tempKeys[4];

	for(size_t i = 0; i<x->__size_; i++){
		tempKeys[i]=x->__keys_[i];
	}
	for(size_t i = 0; i<x->__size_+1; i++){
		tempChildren[i]=x->__children_[i];
	}

	int j = x->__size_-1; // 이때 j는 2, __size_는 3
	while(j>=0 && __key<tempKeys[j]){
		tempKeys[j+1] = tempKeys[j];
		tempChildren[j+2] = tempChildren[j+1];
		j--;
	}
	tempKeys[j+1]=__key;
	tempChildren[j+2]=y;

	int center = size/2; //size에 따라 값이 바뀜.
	_Tp centerKey = tempKeys[center];

	//////////////////////////////////////////////

	int k=0;
	x->__size_ = 0;
	while(k < center){ // ❗❗❗동일한 키가 있다면 : 수정함
		x->__keys_[k] = tempKeys[k];
		x->__children_[k] = tempChildren[k];
		k++;
		x->__size_++;
	}
	x->__children_[k] = tempChildren[k];

	_NodePtr newNode = new Node<_Tp, M>();
	k=center+1;// ❗ 수정함 수도 코드랑비교 필요

	while(k<size){ // size = 4;
		newNode->__keys_[newNode->__size_] = tempKeys[k];
		newNode->__children_[newNode->__size_] = tempChildren[k];
		k++;
		newNode->__size_++;
	}
	newNode->__children_[newNode->__size_]=tempChildren[k];

	return std::make_pair(centerKey, newNode);
}

template <class _NodePtr, class _Tp, std::size_t M>
std::pair<const Node<_Tp>*, bool> __insertBT(_NodePtr& __root, const _Tp& __key) { //❗❗

	_Tp keyCopy = __key; 


	if (__root == nullptr) {
		__root = new Node<_Tp, M>(__key);
		return std::make_pair(__root, true);
	}

	std::pair<std::stack<_NodePtr>, bool> searchPathValue = searchPath<_NodePtr, _Tp, M>(__root, __key);
	std::stack<_NodePtr> pathStack =searchPathValue.first;
	bool result = searchPathValue.second;

	if(result) 
		return std::make_pair(nullptr, false);


	bool finished = false;
	_NodePtr x = pathStack.top(); // 체크하는 노드
	pathStack.pop();
	_NodePtr y = nullptr;  // 오버플로우로 인한 노드 분할로 새로 생성되는 노드

	do{
		if(x->__size_ < 3){ //❗❗일반화 안 함
			insertKey<_NodePtr, _Tp, M>(__root, x, y, keyCopy);
			finished = true;
		}else{
			std::pair<_Tp, _NodePtr> splitNodeResult = splitNode<_NodePtr, _Tp, M>(__root, x, y, keyCopy);
			keyCopy = splitNodeResult.first;
			_NodePtr newNode = splitNodeResult.second;
			y = newNode;
			if(!pathStack.empty())
			{
				x=pathStack.top();
				pathStack.pop();
			}else{ // 마지막 노드임
				__root = new Node<_Tp, M>();
				__root->__keys_[0]=keyCopy;
				__root->__children_[0]=x;
				__root->__children_[1]=y;
				__root->__size_=1;
				finished=true;
			}
		}
	}while(!finished);
	return std::make_pair(__root, true); //루트를 반환


}

template <class _NodePtr, class _Tp, std::size_t M>
void deleteKey(_NodePtr& __root, _NodePtr x, _Tp __key){
    (void)__root;//❗❗
	std::size_t i = 0;

	while(i < x->__size_ && static_cast<int>(__key) > static_cast<int>(x->__keys_[i]))//❗❗ 나중에 수정하기c
	{
		i++;
	}

	if (i >= x->__size_ || static_cast<int>(x->__keys_[i]) != static_cast<int>(__key)) { //❗❗ 나중에 수정하기
        return;     
    }//❗❗ 나중에 수정하기

	while(i<x->__size_){
		x->__keys_[i] = x->__keys_[i+1];
		x->__children_[i+1]=x->__children_[i+2];
		i++;
	}
	//여기다가 한줄추가하면 되는거 아닌가
	x->__children_[x->__size_]=nullptr;
	x->__size_ = x->__size_-1;
}

template <class _NodePtr>
int bestSibling(_NodePtr& __root, _NodePtr x, _NodePtr y){
    (void)__root;//❗❗
	std::size_t i = 0;
    std::size_t index = 0;
	
	while(y->__children_[i]!=x)
	{
		i++;
	}
	if( i==0 ){
		index = i+1;
	}else if(i==y->__size_){
		index = i-1;
	}else if(y->__children_[i-1]->__size_ >= y->__children_[i+1]->__size_){
		index = i-1;
	}else{
		index = i+1;
	}

	return index;
}
template <class _NodePtr, class _Tp, std::size_t M>
void redistribute(_NodePtr& __root, _NodePtr x, _NodePtr y, std::size_t bestSiblingIndex){

	std::size_t i = 0;
	while(y->__children_[i]!=x){
		i++;
	}
	_NodePtr bestNode = y->__children_[bestSiblingIndex];


	if(bestSiblingIndex< static_cast<std::size_t>(i) ){ //❗❗
		_Tp lastKey = bestNode->__keys_[bestNode->__size_-1];
		insertKey<_NodePtr, _Tp, M>(__root, x, (_NodePtr)nullptr, y->__keys_[i-1]);//❗❗
		x->__children_[1]=x->__children_[0]; //❗❗❗넣어야하나?
		x->__children_[0]=bestNode->__children_[bestNode->__size_];
		bestNode->__children_[bestNode->__size_]=nullptr;
		deleteKey<_NodePtr, _Tp, M>(__root, bestNode, lastKey);
		y->__keys_[i-1]=lastKey;
	}else{
		_Tp firstKey = bestNode->__keys_[0];
		insertKey<_NodePtr, _Tp, M>(__root, x, (_NodePtr)nullptr, y->__keys_[i]);
		x->__children_[x->__size_]=bestNode->__children_[0];
		bestNode->__children_[0]=bestNode->__children_[1];
		deleteKey<_NodePtr, _Tp, M>(__root, bestNode, firstKey);
		y->__keys_[i]=firstKey;
	}
}
template <class _NodePtr, class _Tp, std::size_t M>
void mergeNode(_NodePtr& __root, _NodePtr x, _NodePtr y, std::size_t bestSiblingIndex){

	std::size_t i = 0;
	while(y->__children_[i]!=x){
		i++;
	}
    

	_NodePtr bestNode = y->__children_[bestSiblingIndex];



	if(bestSiblingIndex>static_cast<std::size_t>(i)){ //❗❗❗
		// x <-> bestNode 교환
        _NodePtr tempNode = x;
        x = bestNode;
        bestNode = tempNode;

        // i <-> bestSiblingIndex 교환
        std::size_t tempIndex = i;
        i = bestSiblingIndex;
        bestSiblingIndex = tempIndex;
	}
    


    //오른쪽 sibling 을 x에다가 넣는 코드

	bestNode->__keys_[bestNode->__size_] = y->__keys_[i-1];
	bestNode->__size_ = bestNode->__size_+1;
	std::size_t j = 0;


	while(j<x->__size_){
		bestNode->__keys_[bestNode->__size_] = x->__keys_[j];
		bestNode->__children_[bestNode->__size_] = x->__children_[j];
		bestNode->__size_ = bestNode->__size_+1;
		j++;
	}
	bestNode->__children_[bestNode->__size_] = x->__children_[x->__size_];
    

	deleteKey<_NodePtr, _Tp, M>(__root, y, y->__keys_[i-1]);

 // 🔥🔥🔥 여기 추가해야 memory leak이 해결된다!!
    // 부모 y의 children 배열에서 x 제거
    for (size_t k = i; k < y->__size_; k++) {
        y->__children_[k] = y->__children_[k + 1];
    }
    y->__children_[y->__size_] = nullptr;
    // 🔥🔥🔥 여기까지


    // x 실제 삭제
    delete x;
}


template <class _NodePtr, class _Tp, std::size_t M>
const Node<_Tp>* __eraseBT(_NodePtr& __root, const _Tp& __key) { //❗❗

    

	std::pair<std::stack<_NodePtr>, bool> searchPathResult = searchPath<_NodePtr, _Tp, M>(__root, __key);
	std::stack<_NodePtr> pathStack = searchPathResult.first;
	bool searchValue = searchPathResult.second;

	if(searchValue==false){
        
        return nullptr;
    }
	_NodePtr x = pathStack.top();
	_NodePtr y = nullptr;
 	pathStack.pop(); //❗❗수정?

	bool keyInTerminal = true;
	for(size_t i=0; i<x->__size_+1; i++){
		if(x->__children_[i] != nullptr){
			keyInTerminal = false;
			break;
		}
	}

    // 여기서 문제 발생!!
	if(!keyInTerminal){
        
		_NodePtr internalNode = x;
		size_t index = 0;
		for(size_t i=0; i<x->__size_; i++){
			if(x->__keys_[i] == __key){
				index = i;
			}
	    }

        pathStack.push(x);

        std::pair<std::stack<_NodePtr>, bool> searchPathResult2 = searchPath<_NodePtr, _Tp, M>(x->__children_[index+1], x->__keys_[index]);
		std::stack<_NodePtr> pathStack2 = searchPathResult2.first;
		std::stack<_NodePtr> tmpStack;
		while(!pathStack2.empty()){
			_NodePtr value =pathStack2.top();
			pathStack2.pop(); 
			tmpStack.push(value);
		}

		while(!tmpStack.empty()){
			_NodePtr value =tmpStack.top();
			tmpStack.pop(); 
			pathStack.push(value);
		}

		x = pathStack.top();
		pathStack.pop();
		//❗❗수정??
		_Tp tempKey = internalNode->__keys_[index];
		internalNode->__keys_[index] = x->__keys_[0];
		x->__keys_[0]=tempKey;
	} // pathStack은 leafNode까지의 경로
	
	

	
	bool finished = false;


	deleteKey<_NodePtr, _Tp, M>(__root, x, __key);

	if(!pathStack.empty()){
		y = pathStack.top();
		pathStack.pop();
	}

	do{
		if(x==__root || x->__size_ >= 1){ // isRoot 함수 적용해야하나???? // ❗❗하드 코딩 됨
			finished = true;
		}else{
			std::size_t bestSiblingIndex = bestSibling(__root, x, y); //❗❗
			// x: underflow 발생한 노드
			// y: x의 부모 노드
			// bestSibling: x 형제 노드의 인덱스

			if(y->__children_[bestSiblingIndex]->__size_ > 1)// ❗❗하드 코딩 됨
			{
				redistribute<_NodePtr, _Tp, M>(__root, x, y, bestSiblingIndex);
				finished=true;
			}
			else{
				mergeNode<_NodePtr, _Tp, M>(__root, x, y, bestSiblingIndex);
				x=y;
				if(!pathStack.empty()){
					y = pathStack.top();
					pathStack.pop();
				}else{
					finished=true;
				}
			}
		}
	}while(!finished);

	if(y!=nullptr && y->__size_==0){
		__root = y->__children_[0];
		delete y;
	}

	return __root;
}


// 아래는 반드시 사용해야하는 BT 클래스입니다.
template <class _Tp, std::size_t M = 4>
class BT {
	public: // Member types
		typedef _Tp						key_type;
		typedef std::size_t				size_type;
		typedef Node<key_type>*			pointer;
		typedef const Node<key_type>*	const_pointer;
	
	private: // Member variables
		pointer	__root_;
	
	public: // Constructor
		BT(): __root_(nullptr) {}
	
	public: // Lookup
		void inorder() const {
			// use __inorder or write your own code here
			__inorder(__root_);
			std::cout << std::endl;
		}

	public: // Modifier
		std::pair<const_pointer, bool> insert(const key_type& key) {
			// use __insertBT or write your own code here
			return __insertBT<pointer, key_type, M>(__root_, key);//❗❗❗
		}

		const_pointer erase(const key_type& key) {
			// use __eraseBT or write your own code here
			return __eraseBT<pointer, key_type, M>(__root_, key);//❗❗❗
		}

		void clear() {
			// use __clear or write your own code here
			__clear(__root_);
		}
	
	/*
	* 아래는 inorder traversal을 대체할 수 있는 operator<< 입니다.
	* 반드시 아래의 함수를 사용해야할 필요는 없습니다.
	*/
	friend std::ostream& operator<<(std::ostream& os, const BT& tree) {
		os << tree.__root_;
		return os;
	}
};



/*
* 아래는 추천드리는 main 함수의 예시입니다.
* 반드시 아래의 main 함수를 사용해야할 필요는 없습니다.
* ❗️새로 구현하실 경우, 출력 형식에 주의하세요.❗️
*/
int main() {
	BT<int>	tree;
	char	command;
	int		key;

	while (std::cin >> command >> key) {
		switch ((int)command) {
			case (int)'i':
				if (tree.insert(key).second == false) {
					std::cerr << "i " << key << ": The key already exists" << std::endl;
					continue;
				}
				break;
			case (int)'d':
				if (tree.erase(key) == nullptr) {
					std::cerr << "d " << key << ": The key does not exist" << std::endl;
					continue;
				}
				break;
			default:
				std::cerr << "Invalid command: " << command << std::endl;
				return (1);
				break;
		}
		std::cout << tree << std::endl;
	}

	// 프로그램 종료 전, 메모리 누수가 발생하지 않도록 할당받은 메모리를 반드시 해제해야 합니다.
	tree.clear();

	return (0);
}
