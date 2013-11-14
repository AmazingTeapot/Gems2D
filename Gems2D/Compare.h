	class compare {
		
		// simple comparison function
		public:
			bool operator()(const sf::Vector2<int> a, const sf::Vector2<int> b) { 
				if(a.x == b.x) {
					if(a.y > b.y) return true;
				}
				return (a.x - b.x) > 0;
			}
	};