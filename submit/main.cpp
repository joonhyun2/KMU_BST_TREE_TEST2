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
	private: // 노드의 멤버 타입
		typedef _Tp					__key_type;
		typedef Node<__key_type>*	__node_pointer;
		typedef std::size_t			size_type;
	
	public: // 멤버 변수
		__key_type		__keys_[M - 1];
		__node_pointer	__children_[M];
		size_type		__size_;
	
	public: // 기본 생성자
		
    Node() { //처음 생성할 때 자식 포인터의 값을 다 nullptr로 초기화 한다.
        __size_ = 0;
        for (size_type i = 0; i < M; i++)
            __children_[i] = nullptr;
    }

    // Node에 키를 포함해서 생성한다.
    Node(const __key_type& key) {
        __size_ = 0;
        for (size_type i = 0; i < M; i++)
            __children_[i] = nullptr;
        __push_front(key, nullptr);
    }

	public: // 노드에 key값을 한개 와 자식 포인터를 넣는다
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
		// 노드의 맨 뒤에 key와 자식 포인터를 넣는다.
		void __push_back(const __key_type& __key, const __node_pointer& __np) {
			__keys_[size()] = __key;
			__children_[size() + 1] = __np;
			++size();
		}
		// 노드의 맨 앞 key를 제거하고 반환한다.
		__key_type __pop_front() {//노드에 키 갑
			const __key_type __ret = __keys_[0];
			
			for (size_type __i = 0; __i < __size_ - 1; ++__i) {
				__keys_[__i] = __keys_[__i + 1];
				this->__children_[__i] = this->__children_[__i + 1];
			}
			this->__children_[__size_ - 1] = this->__children_[__size_];
			--size();

			return __ret;
		}// 노드의 맨 뒤 key를 제거하고 반환한다.
		__key_type __pop_back() { return __keys_[--size()]; }

	public: // 노드 사이즈를 반환한다. 여기서 사이즈란 key의 개수이다.
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

// 트리를 중위 순회 순으로 출력한다. 
template <class _NodePtr>
void __inorder(_NodePtr __x) {
	// 노드가 없으면 출력하지 않는다.
	if (__x == nullptr || __x->size() == 0) {
		return ;
	}

	std::cout << '<';
	// 오쪽 자식을 출력한다. 
	std::cout << __x->__children_[0] << ' ';
	// key와 key의 오른쪽 자식을 출력한다.
	for (std::size_t __i = 0; __i < __x->size() - 1; __i++) {
		std::cout << __x->__keys_[__i] << ' ';
		if (__x->__children_[__i + 1] != nullptr) {
			std::cout << __x->__children_[__i + 1] << ' ';
		}
	}
	//마지막 키와 자식을 출력한다.
	std::cout << __x->__keys_[__x->size() - 1] << ' ';
	std::cout << __x->__children_[__x->size()];
	std::cout << '>';

	return ; 
}

// 트리 삭제는 중위 순회로 재귀 방식으로 진행한다.
template <class _NodePtr>
void __clear(_NodePtr& __x) {
	if (__x == nullptr) {
		return;
	}
	
	for (std::size_t __i = 0; __i <= __x->size(); __i++) {
		__clear(__x->__children_[__i]);
	}
	// 노드 삭제
	delete __x;
	__x = nullptr;
}

// 루트부터 시작해서 key를 찾고 탐색 경로를 stack으로 반환한다.
template <class _NodePtr, class _Tp, std::size_t M>
std::pair<std::stack<_NodePtr>, bool> searchPath(_NodePtr& __root, const _Tp& __key){
	_NodePtr x = __root;
	std::stack<_NodePtr> path;
	std::size_t i = 0;
	
	do{ 
		i=0;
		while( i<=x->__size_-1 && __key>x->__keys_[i]) //노드에서 key가 삽입할 위치를 탐색한다.
		{
			i++;
		}
		if( i<= x->__size_-1 && __key==x->__keys_[i]){//key를 찾으면 탐색 경로를 반환한다.
			path.push(x);
			return std::pair<std::stack<_NodePtr>, bool>(path,  true);

		}
		//경로에 노드 넣기
		path.push(x);

		// key가 있는 자식 노드로 이동한다.
		x=x->__children_[i];

	} while(x!=nullptr);
	// key를 찾지 못한 경우
	return std::pair<std::stack<_NodePtr>, bool>(path,  false);
}

// x에 key값을 삽입한다.
template <class _NodePtr, class _Tp, std::size_t M>
void insertKey(_NodePtr& __root, _NodePtr x, _NodePtr y, _Tp __key){
    (void)__root; // 루트는 쓰이지 않기에 컴파일 경고를 방지하고 위해 작성함.
	int i = x->__size_-1; 
	// 삽입 위치를 아래와 같이 기존 key를 오른쪽으로 이동하면서 찾는다.
	while(i>=0 && __key<x->__keys_[i]){
		x->__keys_[i+1]=x->__keys_[i];
		x->__children_[i+2]=x->__children_[i+1];
		i--;
	}
	//새 키와 키의 오른 쪽 자식을 넣고 사이즈를 1 증가한다.
	x->__keys_[i+1]=__key;
	x->__children_[i+2]= y;
	x->__size_=x->__size_+1;
}


template <class _NodePtr, class _Tp, std::size_t M>
std::pair<_Tp, _NodePtr> splitNode(_NodePtr& __root, _NodePtr x, _NodePtr y, _Tp __key){
    (void)__root;// 루트는 쓰이지 않기에 컴파일 경고를 방지하고 위해 작성함.
	int size = x->__size_+1; 
	
	_NodePtr tempChildren[M+1];
	_Tp tempKeys[M];


	// 임시 배열에 기존 키 값과 자식 포인터 값을 저장한다.
	for(size_t i = 0; i<x->__size_; i++){
		tempKeys[i]=x->__keys_[i];
	}
	for(size_t i = 0; i<x->__size_+1; i++){
		tempChildren[i]=x->__children_[i];
	}

	int j = x->__size_-1; 
	// key값을 임시 배열에 삽입한다.
	while(j>=0 && __key<tempKeys[j]){
		tempKeys[j+1] = tempKeys[j];
		tempChildren[j+2] = tempChildren[j+1];
		j--;
	}
	tempKeys[j+1]=__key;
	tempChildren[j+2]=y;

	int center = size/2; // 가운데 키 값
	_Tp centerKey = tempKeys[center];



	int k=0;
	x->__size_ = 0;
	while(k < center){ // 가운데 키 왼쪽 부분을 노드 x에 넣는다.
		x->__keys_[k] = tempKeys[k];
		x->__children_[k] = tempChildren[k];
		k++;
		x->__size_++;
	}
	x->__children_[k] = tempChildren[k];

	_NodePtr newNode = new Node<_Tp, M>();
	k=center+1;

	while(k<size){ // 가운데 키 오른쪽 부분을 새 노드에 넣는다.
		newNode->__keys_[newNode->__size_] = tempKeys[k];
		newNode->__children_[newNode->__size_] = tempChildren[k];
		k++;
		newNode->__size_++;
	}
	newNode->__children_[newNode->__size_]=tempChildren[k];

	return std::make_pair(centerKey, newNode);
}

// 트리에 key를 넣고 루트 포인터 + 성공 여부를 반환한다.
template <class _NodePtr, class _Tp, std::size_t M>
std::pair<const Node<_Tp>*, bool> __insertBT(_NodePtr& __root, const _Tp& __key) { //❗❗

	_Tp keyCopy = __key; 


	if (__root == nullptr) { // 트리가 처음부터 없을 시에 새로운 루트 생성
		__root = new Node<_Tp, M>(__key);
		return std::make_pair(__root, true);
	}

	std::pair<std::stack<_NodePtr>, bool> searchPathValue = searchPath<_NodePtr, _Tp, M>(__root, __key);
	std::stack<_NodePtr> pathStack =searchPathValue.first;
	bool result = searchPathValue.second;

	if(result) 
		return std::make_pair(nullptr, false);


	bool finished = false;
	_NodePtr x = pathStack.top(); // 삽입하는 리프 노드
	pathStack.pop();
	_NodePtr y = nullptr;  // 오버플로우로 인한 노드 분할로 새로 생성되는 노드

	do{
		if(x->__size_ < M - 1){ //node에 여유 공간이 있다면 key를 넣는다.
			insertKey<_NodePtr, _Tp, M>(__root, x, y, keyCopy);
			finished = true;
		}else{
			// 공간이 꽉 찼다면 splitNode실행한다.
			std::pair<_Tp, _NodePtr> splitNodeResult = splitNode<_NodePtr, _Tp, M>(__root, x, y, keyCopy);
			// 중앙 키 값은 부모에 넣을 값이다
			keyCopy = splitNodeResult.first;
			_NodePtr newNode = splitNodeResult.second;
			y = newNode;

			if(!pathStack.empty()) //부모 노드에서 삽입을 계속 진행한다.
			{
				x=pathStack.top();
				pathStack.pop();
			}else{ // 최상위 노드에서 splitNode가 발생하면 새로운 루트를 생성한다.
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

// x노드에서 __key값을 삭제한다.
template <class _NodePtr, class _Tp, std::size_t M>
void deleteKey(_NodePtr& __root, _NodePtr x, _Tp __key){
    (void)__root;
	std::size_t i = 0;
	// 삭제하는 키의 위치 구하기
	while(i < x->__size_ && static_cast<int>(__key) > static_cast<int>(x->__keys_[i]))//❗❗ 나중에 수정하기c
	{
		i++;
	}

	if (i >= x->__size_ || static_cast<int>(x->__keys_[i]) != static_cast<int>(__key)) { //❗❗ 나중에 수정하기
        return;     
    }// 삭제하려는 key가 없다면 종료한다.

	//키와 자식 포인터를 한칸씩 왼쪽으로 이동.
	while(i<x->__size_){
		x->__keys_[i] = x->__keys_[i+1];
		x->__children_[i+1]=x->__children_[i+2];
		i++;
	}
	//마지막 자식 포인터를 nullptr로 설정한다.
	x->__children_[x->__size_]=nullptr;
	x->__size_ = x->__size_-1;
}

//재분배와 merge에 사용할 형제를 골라낸다.
template <class _NodePtr>
int bestSibling(_NodePtr& __root, _NodePtr x, _NodePtr y){
    (void)__root;
	std::size_t i = 0;
    std::size_t index = 0;
	
	while(y->__children_[i]!=x)// y노드의 몇번 째가 x인지 찾는다.
	{
		i++;
	}
	if( i==0 ){ // 만약 왼쪽 맨 끝이라면 오른 쪽 형제를 택한다.
		index = i+1;
	}else if(i==y->__size_){ // 오른 쪽 끝이라면 왼쪽 형제 택함.
		index = i-1;
	}else if(y->__children_[i-1]->__size_ >= y->__children_[i+1]->__size_){
		index = i-1; // 왼쪽 형제가 더 크거나 같으면 왼쪽 선택
	}else{
		index = i+1; //오른 쪽 선택
	}

	return index;
}
//  형제 노드에서 key를 가져와 재분배한다.
template <class _NodePtr, class _Tp, std::size_t M>
void redistribute(_NodePtr& __root, _NodePtr x, _NodePtr y, std::size_t bestSiblingIndex){

	std::size_t i = 0;
	while(y->__children_[i]!=x){
		i++;
	}
	_NodePtr bestNode = y->__children_[bestSiblingIndex];//선택된 형제 노드


	if(bestSiblingIndex< static_cast<std::size_t>(i) ){ // 왼쪽에 형제가 있을 때
		_Tp lastKey = bestNode->__keys_[bestNode->__size_-1];
		insertKey<_NodePtr, _Tp, M>(__root, x, (_NodePtr)nullptr, y->__keys_[i-1]);//부모의 키를 x에 삽입한다.
		x->__children_[1]=x->__children_[0]; // x의 기존 자식 포인터를 오른쪽으로 한 칸 이동.
		x->__children_[0]=bestNode->__children_[bestNode->__size_];// 왼쪽 형제의 마지막 child를 x의 첫 child로 가져온다.
		bestNode->__children_[bestNode->__size_]=nullptr;// 형제의 child를 이동했으므로 빈 자리 nullptr로 초기화한다.
		deleteKey<_NodePtr, _Tp, M>(__root, bestNode, lastKey);// 형제 노드에서 마지막 key를 삭제한다.
		y->__keys_[i-1]=lastKey;// 부모 키를 교체한다.
	}else{ // 오른쪽에 형제가 있을 때
		_Tp firstKey = bestNode->__keys_[0];
		insertKey<_NodePtr, _Tp, M>(__root, x, (_NodePtr)nullptr, y->__keys_[i]);
		x->__children_[x->__size_]=bestNode->__children_[0];
		bestNode->__children_[0]=bestNode->__children_[1];
		deleteKey<_NodePtr, _Tp, M>(__root, bestNode, firstKey);
		y->__keys_[i]=firstKey;
	}
}
//x와 형제 노드를 합친다.
template <class _NodePtr, class _Tp, std::size_t M>
void mergeNode(_NodePtr& __root, _NodePtr x, _NodePtr y, std::size_t bestSiblingIndex){

	std::size_t i = 0;
	while(y->__children_[i]!=x){// x의 위치를 부모에서 찾는다.
		i++;
	}
    

	_NodePtr bestNode = y->__children_[bestSiblingIndex];// 병합 되는 형제 노드



	if(bestSiblingIndex>static_cast<std::size_t>(i)){ //형제노드가 오른쪽이라면 x와 위치를 바꾼다.
        _NodePtr tempNode = x;
        x = bestNode;
        bestNode = tempNode;

        // i <-> bestSiblingIndex 교환
        std::size_t tempIndex = i;
        i = bestSiblingIndex;
        bestSiblingIndex = tempIndex;
	}
    


    //부모 키 값을 형제 노드에 가져온다 이후 merge를 한다.
	bestNode->__keys_[bestNode->__size_] = y->__keys_[i-1];
	bestNode->__size_ = bestNode->__size_+1;
	std::size_t j = 0;


	while(j<x->__size_){ // x의 키 값들이 형제노드에 merge된다.
		bestNode->__keys_[bestNode->__size_] = x->__keys_[j];
		bestNode->__children_[bestNode->__size_] = x->__children_[j];
		bestNode->__size_ = bestNode->__size_+1;
		j++;
	}
	bestNode->__children_[bestNode->__size_] = x->__children_[x->__size_];
    
	// 부모에서 가져온 key 없앰
	deleteKey<_NodePtr, _Tp, M>(__root, y, y->__keys_[i-1]);


    // 기존 x노드 삭제
    delete x;
}


template <class _NodePtr, class _Tp, std::size_t M>
const Node<_Tp>* __eraseBT(_NodePtr& __root, const _Tp& __key) {

		// 루트가 없다면 삭제 x
		if(__root == nullptr){
			return nullptr;
		}
		// 삭제 대상 키 값을 찾고 경로를 pathStack에 저장한다.
	std::pair<std::stack<_NodePtr>, bool> searchPathResult = searchPath<_NodePtr, _Tp, M>(__root, __key);
	std::stack<_NodePtr> pathStack = searchPathResult.first;
	bool searchValue = searchPathResult.second;

	if(searchValue==false){
        
        return nullptr; // 삭제할 키가 없음
    }
	//삭제할 노드를 x에 저장
	_NodePtr x = pathStack.top();
	_NodePtr y = nullptr;
 	pathStack.pop(); 

	// 해당 노드가 터미널인지 확인
	bool keyInTerminal = true;
	for(size_t i=0; i<x->__size_+1; i++){
		if(x->__children_[i] != nullptr){
			keyInTerminal = false;
			break;
		}
	}

    
	if(!keyInTerminal){ // 삭제 노드가 내부 노드면 오른쪽 subtree의 가장 작은 키값과 교환한다.
        
		_NodePtr internalNode = x;
		size_t index = 0;
		for(size_t i=0; i<x->__size_; i++){ // 삭제할 노드 찾기
			if(x->__keys_[i] == __key){
				index = i;
				break; 
			}
	    }

        pathStack.push(x);

        std::pair<std::stack<_NodePtr>, bool> searchPathResult2 = searchPath<_NodePtr, _Tp, M>(x->__children_[index+1], x->__keys_[index]);//삭제 노드를 찾기 위해 subtree를 탐색한다.
		std::stack<_NodePtr> pathStack2 = searchPathResult2.first;
		std::stack<_NodePtr> tmpStack;

		// 삭제할 경로를 정상 순서로 만들어 기존 pathStack 뒤에 이어 붙여 준다.
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
		// 내부 노드 삭제를 위해 key값  자리를 바꾼다.
		_Tp tempKey = internalNode->__keys_[index];
		internalNode->__keys_[index] = x->__keys_[0];
		x->__keys_[0]=tempKey;
	} 
	
	
 
	
	bool finished = false;

	// 실제 key값을 없앤다.
	deleteKey<_NodePtr, _Tp, M>(__root, x, __key);

	// 루트가 비워졌다면 트리를 완전히 삭제한다.
	// 성공을 나타내기 위해 nullptr이 이 아닌 임의의 값 1을 반환한다.
	if(x == __root && x->__size_ == 0){
		delete __root;
		__root = nullptr;
		return (const Node<_Tp>*)1; // 삭제 성공을 나타내는 더미 (nullptr이 아닌 값)
	}

	if(!pathStack.empty()){// 부모 노드
		y = pathStack.top();
		pathStack.pop();
	}

	do{ 
		if(x==__root || x->__size_ >= (M-1)/2){ 
			finished = true;
		}else{// 형제 노드 선택
			std::size_t bestSiblingIndex = bestSibling(__root, x, y); 
			
			// 형제 노드가 여유가 있으면 키를 가져온다.
			if(y->__children_[bestSiblingIndex]->__size_ >(M-1)/2)// 하드코딩
			{
				redistribute<_NodePtr, _Tp, M>(__root, x, y, bestSiblingIndex);
				finished=true;
			}
			else{// 형제도 부족하면 병합
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
	}while(!finished); // 마지막에 루트가 비어 있으면 자식을 새 루트로 바꿔 준다.

		if(__root != nullptr && __root->__size_ == 0){
		_NodePtr oldRoot = __root;
		__root = __root->__children_[0];  
		delete oldRoot;                    
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
			return __insertBT<pointer, key_type, M>(__root_, key);
		}

		const_pointer erase(const key_type& key) {
			// use __eraseBT or write your own code here
			return __eraseBT<pointer, key_type, M>(__root_, key);
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
}////
