import { useState } from 'react'

export type Platform = 'Browser' | 'Node'

export function getPlatform(): Platform {
  return typeof window !== 'undefined' ? 'Browser' : 'Node'
}

export default function usePlatform(): Platform {
  const [platform] = useState(getPlatform)
  return platform
}
