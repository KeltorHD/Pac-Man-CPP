#ifndef MAP_H

class Map
{
public:
	enum class tileType
	{
		free,       /*свободная клетка*/
		food,       /*еда*/
		energizere, /*энерджайзер*/
		wall_l,     /*стена левая*/
		wall_r,     /*стена правая*/
		wall_u,     /*стена верхняя*/
		wall_d,     /*стена нижняя*/
		wall_
	};
private:

};


#endif // ! MAP_H