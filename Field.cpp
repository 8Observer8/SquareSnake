#include <cstdlib>
#include <ctime>
#include "Field.h"
#include "Painter.h"

Field::Field()
{
    for ( int y = 0; y < Field::HEIGHT; ++y ) {
        for ( int x = 0; x < Field::WIDTH; ++x ) {
            m_m[y][x] = Field::EMPTY;
        }
    }

    this->newFruit();
}

void Field::setBlock( Field::Type type, int x, int y )
{
    m_m[y][x] = type;
}

Field::Type Field::block( int x, int y ) const
{
    return m_m[y][x];
}

void Field::draw( Painter &p ) const
{
    for ( int y = 0; y < Field::HEIGHT; ++y ) {
        for ( int x = 0; x < Field::WIDTH; ++x ) {
            switch ( m_m[y][x] ) {
                case Field::EMPTY:
                    break;
                case Field::SNAKE_BLOCK:
                    p.bar( x * Field::BLOCK_WIDTH,
                           y * Field::BLOCK_HEIGHT,
                           ( x + 1 ) * Field::BLOCK_WIDTH - 1,
                           ( y + 1 ) * Field::BLOCK_HEIGHT - 1 );
                    break;
                case Field::FRUIT:
                    p.circle( x * Field::BLOCK_WIDTH + Field::BLOCK_WIDTH / 2,
                              y * Field::BLOCK_HEIGHT + Field::BLOCK_HEIGHT / 2,
                              Field::BLOCK_WIDTH / 2 - 1 );
            }
        }
    }
}

void Field::newFruit()
{
    int x, y;
    std::srand( std::time( NULL ) );
    do {
        x = std::rand() % Field::WIDTH;
        y = std::rand() % Field::HEIGHT;
    } while ( this->block( x, y ) != Field::EMPTY );
    this->setBlock( Field::FRUIT, x, y );
}
