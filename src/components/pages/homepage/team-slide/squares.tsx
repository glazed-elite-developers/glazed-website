import { IGatsbyImageData } from 'gatsby-plugin-image'

export type Developer = {
  key: string
  name: string
  skills: Array<string>
  description: string
  shortDescription: string
  linkedInUrl: string
  photo: IGatsbyImageData
}

export type DeveloperSquare = { type: 'DeveloperSquare'; developerKey: string }

export type Square =
  | DeveloperSquare
  | { type: 'TitleSquare'; content: string }
  | { type: 'MottoSquare'; content: string }
  | { type: 'SendApplicationSquare' }

const FixedSquares: Array<[position: number, Square]> = [
  [0, { type: 'TitleSquare', content: '// team' }],
  [4, { type: 'MottoSquare', content: 'Great developers build great code' }],
  [11, { type: 'MottoSquare', content: 'Great developers love their work' }],
  [12, { type: 'SendApplicationSquare' }],
]

export function buildDeveloperSquares(developers: Array<Developer>) {
  const developerSquares = developers.map<DeveloperSquare>((developer) => ({
    type: 'DeveloperSquare',
    developerKey: developer.key,
  }))
  return FixedSquares.reduce<Array<Square>>(
    (result, [index, square]) => [
      ...result.slice(0, index),
      square,
      ...result.slice(index),
    ],
    developerSquares
  )
}
