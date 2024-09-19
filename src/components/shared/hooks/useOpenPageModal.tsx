import { useCallback } from 'react'
import { useLocation } from '@reach/router'
import { getFullPath, navigate } from '../Routing'

export default function useOpenPageModal(modal: 'say-hello' | 'job-offer'): {
  modalUrl: string
  openModal: (event: React.MouseEvent<HTMLAnchorElement>) => void
} {
  const location = useLocation()
  const currentPath = location.pathname
  const currentFullPath = encodeURIComponent(getFullPath(location))
  const modalUrl = `${currentPath}?modal=${modal}&backTo=${currentFullPath}`
  const openModal = useCallback(
    (event: React.MouseEvent<HTMLAnchorElement>) => {
      event.preventDefault()
      navigate({ preventDefaultScrollBehavior: true }, undefined, modalUrl)
    },
    [modalUrl]
  )

  return { modalUrl, openModal }
}
